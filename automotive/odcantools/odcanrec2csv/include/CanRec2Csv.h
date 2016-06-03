/**
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

#ifndef CANREC2CSV_H_
#define CANREC2CSV_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"

#include "opendavinci/odcore/reflection/CSVFromVisitableVisitor.h"

#define MAX_CSVs 9

namespace odrec2csv {

    using namespace std;
    using namespace odcore::reflection;
    /**
     * This class can be used to simply display data distributed
     * using a conference.
     */
    class Rec2csv : public odcore::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Rec2csv(const Rec2csv &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Rec2csv& operator=(const Rec2csv &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Rec2csv(const int32_t &argc, char **argv);

            virtual ~Rec2csv();

            odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            odcore::base::FIFOQueue m_fifo;

            virtual void setUp();

            virtual void tearDown();
            
            CSVFromVisitableVisitor* m_csvs[MAX_CSVs];
            ofstream* m_csv_files[MAX_CSVs];
    };

} // odrec2csv

#endif /*CANREC2CSV_H_*/
