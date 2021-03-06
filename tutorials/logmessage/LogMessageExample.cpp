/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <iostream>

#include "LogMessageExample.h"

using namespace std;

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace odcore::base::module;

LogMessageExample::LogMessageExample(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "LogMessageExample")
{}

LogMessageExample::~LogMessageExample() {}

void LogMessageExample::setUp() {
    cout << "This method is called before the component's body is executed." << endl;
}

void LogMessageExample::tearDown() {
    cout << "This method is called after the program flow returns from the component's body." << endl;
}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode LogMessageExample::body() {
    cout << "Hello OpenDaVINCI World!" << endl;

    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
       toLogger(odcore::data::LogMessage::INFO, "This is an info message.");
       toLogger(odcore::data::LogMessage::WARN, "This is an warn message.");
       toLogger(odcore::data::LogMessage::DEBUG, "This is an debug message.");
    }

    return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}

