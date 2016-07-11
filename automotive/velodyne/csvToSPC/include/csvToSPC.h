/**
 * csvToSPC reads a csv file which contains data of Sick lidar (radius, angle, x, y) 
 * and sends out the shared point cloud periodically.
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

#ifndef CSVTOSPAC_H_
#define CSVTOSPAC_H_

//#include <memory>
#include <fstream>
#include <memory>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include "opendavinci/generated/odcore/data/SharedPointCloud.h"

namespace automotive {

        using namespace std;
        /**
         * This class is a skeleton to send driving commands to Hesperia-light's vehicle driving dynamics simulation.
         */
        class csvToSPC : public odcore::base::module::TimeTriggeredConferenceClientModule {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                csvToSPC(const csvToSPC &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                csvToSPC& operator=(const csvToSPC &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                csvToSPC(const int32_t &argc, char **argv);

                virtual ~csvToSPC();

                odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            private:
                virtual void setUp();

                virtual void tearDown();
                
                fstream lidarData;   
                const std::string NAME = "pointCloud";
                const uint32_t POINT_SIZE = 400;
                const uint32_t SIZE_PER_COMPONENT = sizeof(float);
                const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
                const uint32_t SIZE = POINT_SIZE * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT; // What is the total size of the shared memory?  
                std::shared_ptr<odcore::wrapper::SharedMemory> m_velodyneSharedMemory; //Shared memory for the shared point cloud
                odcore::data::SharedPointCloud m_spc;//shared point cloud
                bool stop;
                //odcore::io::conference::ContainerConference &m_conference;
        };

} // automotive

#endif /*CSVTOSPAC_H_*/
