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

#ifndef CANREC2CSVTESTSUITE_H_
#define CANREC2CSVTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <iomanip>

// Include local header files.
#include "../include/CanRec2Csv.h"

#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Pedals.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/AccelerationRequest.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/BrakeRequest.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/SteeringRequest.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Axles.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Propulsion.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/VehicleState.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Wheels.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Steering.h"

using namespace std;
using namespace odcore::data;

using namespace odrec2csv;

/**
 * This class derives from SensorBoard to allow access to protected methods.
 */
class CanRec2CsvTestling : public Rec2Csv {
    private:
        CanRec2CsvTestling();
    
    public:
        CanRec2CsvTestling(const int32_t &argc, char **argv) : Rec2Csv(argc, argv) {}
        
        void publicProcessContainer(Container c)
        {
            return processContainer(c);
        }
        
        string getOutput(int i)
        {
            return m_outputs[i].str();
        }
};

class Alien : public odcore::data::SerializableData, public odcore::base::Visitable {
    public:
        Alien() :
            m_value1(0.0),m_value2(0.0)
        {}
        Alien(double x, double y) :
            m_value1(x),m_value2(y)
        {}
        virtual ~Alien()
        {}
		Alien(const Alien &obj) :
		    m_value1(obj.m_value1),m_value2(obj.m_value2)
		{}
		Alien& operator=(const Alien &obj)
		{
		    m_value1=obj.m_value1;
		    m_value2=obj.m_value2;
		    return (*this);
		}
		virtual ostream& operator<<(ostream &out) const {return out;}
		virtual istream& operator>>(istream &in) {return in;}
		virtual int32_t getID() const {return -1;}
		virtual const string getShortName() const {return "Alien";}
		virtual const string getLongName() const {return "Alien";}
		virtual const string toString() const {return "Alien value1 "+std::to_string(m_value1)+", value2 "+std::to_string(m_value1);}
		
		void accept(odcore::base::Visitor &v)
		{
		    v.beginVisit();
		    v.visit(1, 1, "Alien.value1", "value1", m_value1);
		    v.visit(2, 2, "Alien.value2", "value2", m_value2);
		    v.endVisit();
		}
        double m_value1, m_value2;
};

/**
 * The actual testsuite starts here.
 */
class CanRec2CsvTest : public CxxTest::TestSuite {
    public : 
        CanRec2CsvTestling* t;
    /**
     * This method will be called before each testXYZ-method.
     */
    void setUp() {
        // Prepare the data that would be available from commandline.
        string argv0("canrec2csv");
        string argv1("--cid=100");
        int32_t argc = 2;
        char **argv;
        argv = new char*[2];
        argv[0] = const_cast<char*>(argv0.c_str());
        argv[1] = const_cast<char*>(argv1.c_str());

        // Create an instance of sensorboard through SensorBoardTestling which will be deleted in tearDown().
        t = new CanRec2CsvTestling(argc, argv);
    }

    /**
     * This method will be called after each testXYZ-method.
     */
    void tearDown() {
        delete t;
        t=NULL;
    }

    void testPedalsContainer2Csv() {
        double dummyDouble1=1.2,dummyDouble2=3.4,dummyDouble3=-5.6;
        stringstream testPedalsResult;
        testPedalsResult << "accelerationPedalPosition,brakePedalPosition,torsionBarTorque,Sent_TimeStamp,Received_TimeStamp," << endl
                         << std::fixed << std::setprecision(1) << dummyDouble1 << "," << dummyDouble2 << "," << dummyDouble3 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::Pedals temp;
        temp.setAccelerationPedalPosition(dummyDouble1);
        temp.setBrakePedalPosition(dummyDouble2);
        temp.setTorsionBarTorque(dummyDouble3);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testPedalsResult.str(),t->getOutput(0));
    }
    
    void testAccelerationRequestContainer2Csv() {
        double dummyDouble1=5.3;
        bool dummyBool=true;
        stringstream testAccelerationRequestResult;
        testAccelerationRequestResult   << "enableRequest,accelerationPedalPosition,Sent_TimeStamp,Received_TimeStamp," << endl;
        if(dummyBool) testAccelerationRequestResult<<"1,"; else testAccelerationRequestResult<<"0,";
        testAccelerationRequestResult << std::fixed << std::setprecision(1) << dummyDouble1 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::AccelerationRequest temp;
        temp.setEnableRequest(dummyBool);
        temp.setAccelerationPedalPosition(dummyDouble1);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testAccelerationRequestResult.str(),t->getOutput(1));
    }
    
    void testBrakeRequestContainer2Csv() {
        double dummyDouble1=-15.3;
        bool dummyBool=true;
        stringstream testBrakeRequestResult;
        testBrakeRequestResult   << "enableRequest,brake,Sent_TimeStamp,Received_TimeStamp," << endl;
        if(dummyBool) testBrakeRequestResult<<"1,"; else testBrakeRequestResult<<"0,";
        testBrakeRequestResult << std::fixed << std::setprecision(1) << dummyDouble1 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::BrakeRequest temp;
        temp.setEnableRequest(dummyBool);
        temp.setBrake(dummyDouble1);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testBrakeRequestResult.str(),t->getOutput(2));
    }
    
    void testSteeringRequestContainer2Csv() {
        double dummyDouble1=35.5, dummyDouble2=0.52;
        bool dummyBool=true;
        stringstream testSteeringRequestResult;
        testSteeringRequestResult   << "enableRequest,steeringRoadWheelAngle,steeringDeltaTorque,Sent_TimeStamp,Received_TimeStamp," << endl;
        if(dummyBool) testSteeringRequestResult<<"1,"; else testSteeringRequestResult<<"0,";
        testSteeringRequestResult << std::fixed << std::setprecision(1) << dummyDouble1 << "," << std::setprecision(2) << dummyDouble2 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::SteeringRequest temp;
        temp.setEnableRequest(dummyBool);
        temp.setSteeringRoadWheelAngle(dummyDouble1);
        temp.setSteeringDeltaTorque(dummyDouble2);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testSteeringRequestResult.str(),t->getOutput(3));
    }
    
    void testAxlesContainer2Csv() {
        double dummyDouble1=-1.11,dummyDouble2=0.09,dummyDouble3=-53.05;
        stringstream testAxlesResult;
        testAxlesResult << "loadAxle11,loadAxle12,loadAxle13,Sent_TimeStamp,Received_TimeStamp," << endl
                        << std::fixed << std::setprecision(2) << dummyDouble1 << "," << dummyDouble2 << "," << dummyDouble3 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::Axles temp;
        temp.setLoadAxle11(dummyDouble1);
        temp.setLoadAxle12(dummyDouble2);
        temp.setLoadAxle13(dummyDouble3);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testAxlesResult.str(),t->getOutput(4));
    }
    
    void testPropulsionContainer2Csv() {
        double dummyDouble1=123.45;
        stringstream testPropulsionResult;
        testPropulsionResult << "propulsionShaftVehicleSpeed,Sent_TimeStamp,Received_TimeStamp," << endl
                        << std::fixed << std::setprecision(2) << dummyDouble1 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::Propulsion temp;
        temp.setPropulsionShaftVehicleSpeed(dummyDouble1);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testPropulsionResult.str(),t->getOutput(5));
    }
    
    void testVehicleStateContainer2Csv() {
        double dummyDouble1=99.99,dummyDouble2=3.14,dummyDouble3=-3.14;
        stringstream testVehicleStateResult;
        testVehicleStateResult << "accelerationX,accelerationY,yawRate,Sent_TimeStamp,Received_TimeStamp," << endl
                        << std::fixed << std::setprecision(2) << dummyDouble1 << "," << dummyDouble2 << "," << dummyDouble3 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::VehicleState temp;
        temp.setAccelerationX(dummyDouble1);
        temp.setAccelerationY(dummyDouble2);
        temp.setYawRate(dummyDouble3);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testVehicleStateResult.str(),t->getOutput(6));
    }
    
    void testWheelsContainer2Csv() {
        double dummyDouble1=98.765,dummyDouble2=102938,dummyDouble3=0.05,dummyDouble4=-0.05,dummyDouble5=-237.01,dummyDouble6=999.99;
        stringstream testWheelsResult;
        testWheelsResult << "speedWheel111,speedWheel112,speedWheel121,speedWheel122,speedWheel131,speedWheel132,Sent_TimeStamp,Received_TimeStamp," << endl
                         << std::fixed << std::setprecision(3) << dummyDouble1 << "," << std::setprecision(0) << dummyDouble2 << "," << std::setprecision(2) << dummyDouble3 << "," 
                         << dummyDouble4 << "," << dummyDouble5 << "," << dummyDouble6 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::Wheels temp;
        temp.setSpeedWheel111(dummyDouble1);
        temp.setSpeedWheel112(dummyDouble2);
        temp.setSpeedWheel121(dummyDouble3);
        temp.setSpeedWheel122(dummyDouble4);
        temp.setSpeedWheel131(dummyDouble5);
        temp.setSpeedWheel132(dummyDouble6);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testWheelsResult.str(),t->getOutput(7));
    }
    
    void testSteeringContainer2Csv() {
        double dummyDouble1=0.99,dummyDouble2=-93.47;
        stringstream testSteeringResult;
        testSteeringResult << "roadwheelangle,steeringwheelangle,Sent_TimeStamp,Received_TimeStamp," << endl
                        << std::fixed << std::setprecision(2) << dummyDouble1 << "," << dummyDouble2 << ",0,0," << endl ;
        
        from::opendlv::proxy::reverefh16::Steering temp;
        temp.setRoadwheelangle(dummyDouble1);
        temp.setSteeringwheelangle(dummyDouble2);
        Container c(temp);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(8));
    }
    
    void testAlienContainer() {
        Alien alien(3.14,-6.66);
        stringstream testSteeringResult;
        testSteeringResult.str("");
        Container c(alien);
        
        t->publicProcessContainer(c);
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(0));
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(1));
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(2));
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(3));
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(4));
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(5));
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(6));
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(7));
        TS_ASSERT_EQUALS(testSteeringResult.str(),t->getOutput(8));
    }
};
#endif /*CANREC2CSVTESTSUITE_H_*/

