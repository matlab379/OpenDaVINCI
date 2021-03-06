/**
 * odsplit - Tool for splitting recorded data
 * Copyright (C) 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SPLITTESTSUITE_H_
#define SPLITTESTSUITE_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "cxxtest/TestSuite.h"

#include <memory>
#include "opendavinci/odcore/strings/StringToolbox.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "opendavinci/odtools/player/Player.h"
#include "opendavinci/odtools/recorder/Recorder.h"

// Include local header files.
#include "../include/Split.h"

using namespace std;
using namespace odcore;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::io;
using namespace odcore::io::conference;
using namespace odcore::data::dmcp;
using namespace odtools::player;
using namespace odtools::recorder;
using namespace odsplit;

// Size of the memory buffer.
const uint32_t MEMORY_SEGMENT_SIZE = 100;

// Number of memory segments can be set to a fixed value.
const uint32_t NUMBER_OF_SEGMENTS = 1;

/**
 * The actual testsuite starts here.
 */
class SplitTest : public CxxTest::TestSuite {
    public:
        void setUp() {
            // Run recorder in synchronous mode.
            const bool THREADING = false;
            const bool DUMP_SHARED_DATA = true;
            const string file("file://A.rec");
            Recorder recorder(file, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING, DUMP_SHARED_DATA);

            {
                std::shared_ptr<odcore::wrapper::SharedMemory> memServer = odcore::wrapper::SharedMemoryFactory::createSharedMemory("SharedMemoryServer", 50);
                TS_ASSERT(memServer->isValid());
                TS_ASSERT(memServer->getSize() == 50);

                // Create some test data.
                for(uint32_t i = 0; i < 200; i++) {
                    // Create regular container.
                    TimeStamp t(i, 0);
                    Container c(t);
                    c.setSampleTimeStamp(TimeStamp(i,500));
                    recorder.store(c);

                    // Create shared memory.
                    memServer->lock();
                        stringstream sstr;
                        sstr << "Data-" << i << endl;
                        memcpy(memServer->getSharedMemory(), sstr.str().c_str(), sstr.str().size());
                    memServer->unlock();

                    odcore::data::SharedData sd(memServer->getName(), memServer->getSize());

                    Container c2(sd);
                    c2.setSampleTimeStamp(TimeStamp(i,1000));
                    recorder.store(c2);
                }
            }
        }

        void tearDown() {
            UNLINK("A.rec");
            UNLINK("A.rec.mem");
        }

        ////////////////////////////////////////////////////////////////////////////////////
        // Below this line the actual testcases are defined.
        ////////////////////////////////////////////////////////////////////////////////////

        void testSplitSuccessfullySplit() {
            // Prepare the data that would be available from commandline.
            string argv0("odsplit");
            string argv1("--source=A.rec");
            string argv2("--range=50-60");
            string argv3("--memorysegmentsize=1000");
            int32_t argc = 4;
            char **argv;
            argv = new char*[4];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());
            argv[3] = const_cast<char*>(argv3.c_str());

            // Create an instance of split.
            Split split;

            // Run the split.
            TS_ASSERT(split.run(argc, argv) == 0);

            // Compare the split.

            // Stop playback at EOF.
            const bool AUTO_REWIND = false;
            // Run player in synchronous mode.
            const bool THREADING = false;
            // Construct player.
            string file("file://A.rec_50-60.rec");
            Player player(file, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING);

            int32_t rangeBasis = 25;
            int32_t sharedMemorySegments = 0;
            const uint32_t MAX_ITERATIONS = 1000;
            uint32_t i = 0;

            std::shared_ptr<odcore::wrapper::SharedMemory> memClient;

            while (player.hasMoreData() && (i < MAX_ITERATIONS)) {
                i++;
                // Get container to be sent.
                Container nextContainer = player.getNextContainerToBeSent();

                if (nextContainer.getDataType() == TimeStamp::ID()) {
                    TimeStamp ts = nextContainer.getData<TimeStamp>();
                    TS_ASSERT(ts.getSeconds() == rangeBasis);
                    rangeBasis++;
                }
                else if (nextContainer.getDataType() == odcore::data::SharedData::ID()) {
                    if (!memClient.get()) {
                        odcore::data::SharedData sd = nextContainer.getData<odcore::data::SharedData>();
                        memClient = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sd.getName());
                    }

                    TS_ASSERT(memClient->isValid());
                    TS_ASSERT(memClient->getSize() == 50);
                    memClient->lock();
                        char *c = (char*)(memClient->getSharedMemory());
                        string s(c);

                        stringstream sstr2;
                        sstr2 << "Data-" << (rangeBasis-1) << endl;

                        TS_ASSERT(odcore::strings::StringToolbox::equalsIgnoreCase(s, sstr2.str()));
                    memClient->unlock();

                    sharedMemorySegments++;
                }
            }

            // As the range is given as 50-60, the 6 TimeStamps (delivered at 25, 26, 27, ..., counter will be 31 at the end) and 5 SharedMemory segments will be handled.
            TS_ASSERT(rangeBasis == 31);
            TS_ASSERT(sharedMemorySegments == 5);

            // Clean up temporarily created files.
            UNLINK("A.rec_50-60.rec");
            UNLINK("A.rec_50-60.rec.mem");
        }

        void testSplitWrongRange() {
            // Prepare the data that would be available from commandline.
            string argv0("odsplit");
            string argv1("--source=A.rec");
            string argv2("--range=70-60");
            string argv3("--memorysegmentsize=1000");
            int32_t argc = 4;
            char **argv;
            argv = new char*[4];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());
            argv[3] = const_cast<char*>(argv3.c_str());

            // Create an instance of split.
            Split split;

            // Run the split.
            TS_ASSERT(split.run(argc, argv) == 1);
        }
};

#endif /*SPLITTESTSUITE_H_*/

