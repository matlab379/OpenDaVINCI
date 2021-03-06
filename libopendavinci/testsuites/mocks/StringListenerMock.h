/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#ifndef MOCKS__STRINGLISTENERMOCK_H
#define MOCKS__STRINGLISTENERMOCK_H

#include <string>

#include "FunctionCallWaiter.h"
#include "ParameterValueList.h"
#include "opendavinci/odcore/io/StringListener.h"

namespace mocks {

    class StringListenerMock : public odcore::io::StringListener {
        public:
            StringListenerMock() :
                CALLWAITER_nextString(),
                VALUES_nextString(),
                currentValue()
            {}

            virtual void nextString(const std::string &s) {
                currentValue = s;
                CALLWAITER_nextString.called();
            }

            bool correctCalled() {
                return ( currentValue == VALUES_nextString.getCurrentItem() );
            }

            FunctionCallWaiter CALLWAITER_nextString;
            ParameterValueList< std::string > VALUES_nextString;
        private:
            std::string currentValue;
    };
}
#endif
