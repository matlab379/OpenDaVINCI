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

#include <iostream>

#include "CanRec2Csv.h"
#include "opendavinci/odcore/reflection/CSVFromVisitableVisitor.h"
#include "opendavinci/odcore/reflection/Message.h"
#include "opendavinci/odcore/reflection/MessageFromVisitableVisitor.h"

#include "automotivedata/generated/from/opendlv/proxy/reverefh16/ManualControl.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/AccelerationRequest.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/BrakeRequest.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/SteeringRequest.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Axles.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Propulsion.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/VehicleState.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Wheels.h"
#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Steering.h"

namespace odrec2csv {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::reflection;
    using namespace odcore::data;

    Rec2csv::Rec2csv(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odcanrec2csv"),
        m_fifo() {}

    Rec2csv::~Rec2csv() {}

    void Rec2csv::setUp() {}

    void Rec2csv::tearDown() {}

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Rec2csv::body() {
        addDataStoreFor(m_fifo);
        
        stringstream output_ar;
        stringstream output_br;
        stringstream output_sr;
        stringstream output_a;
        stringstream output_p;
        stringstream output_vs;
        stringstream output_w;
        stringstream output_s;
        CSVFromVisitableVisitor csv_ar(output_ar, true, ',');
        CSVFromVisitableVisitor csv_br(output_br, true, ',');
        CSVFromVisitableVisitor csv_sr(output_sr, true, ',');
        CSVFromVisitableVisitor csv_a(output_a, true, ',');
        CSVFromVisitableVisitor csv_p(output_p, true, ',');
        CSVFromVisitableVisitor csv_vs(output_vs, true, ',');
        CSVFromVisitableVisitor csv_w(output_w, true, ',');
        CSVFromVisitableVisitor csv_s(output_s, true, ',');
                
        Message m_ar,m_br,m_sr,m_a,m_p,m_vs,m_w,m_s;
        
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
            while (!m_fifo.isEmpty()) {
                Container c = m_fifo.leave();
                
                cout << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << "-->" << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() << " dt = " << (c.getReceivedTimeStamp() - c.getSentTimeStamp()).toString() << " ID = " << c.getDataType() << endl; 
                
                
//message from.opendlv.proxy.reverefh16.AccelerationRequest [id = 192]
//message from.opendlv.proxy.reverefh16.BrakeRequest [id = 193]
//message from.opendlv.proxy.reverefh16.SteeringRequest [id = 194]
//message from.opendlv.proxy.reverefh16.Axles [id = 195]
//message from.opendlv.proxy.reverefh16.Propulsion [id = 196]
//message from.opendlv.proxy.reverefh16.VehicleState [id = 197]
//message from.opendlv.proxy.reverefh16.Wheels [id = 198]
//message from.opendlv.proxy.reverefh16.Steering [id = 199]
                
                switch(c.getDataType())
                {
                    case 192:
                    {
                        from::opendlv::proxy::reverefh16::AccelerationRequest temp=c.getData<from::opendlv::proxy::reverefh16::AccelerationRequest>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        m_ar=mfvv.getMessage();
                        m_ar.accept(csv_ar);
                    }
                    break;
                    case 193:
                    {
                        from::opendlv::proxy::reverefh16::BrakeRequest temp=c.getData<from::opendlv::proxy::reverefh16::BrakeRequest>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        m_br=mfvv.getMessage();
                        m_br.accept(csv_br);
                    }
                    break;
                    case 194:
                    {
                        from::opendlv::proxy::reverefh16::SteeringRequest temp=c.getData<from::opendlv::proxy::reverefh16::SteeringRequest>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        m_sr=mfvv.getMessage();
                        m_sr.accept(csv_sr);
                    }
                    break;
                    case 195:
                    {
                        from::opendlv::proxy::reverefh16::Axles temp=c.getData<from::opendlv::proxy::reverefh16::Axles>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        m_a=mfvv.getMessage();
                        m_a.accept(csv_a);
                    }
                    break;
                    case 196:
                    {
                        from::opendlv::proxy::reverefh16::Propulsion temp=c.getData<from::opendlv::proxy::reverefh16::Propulsion>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        m_p=mfvv.getMessage();
                        m_p.accept(csv_p);
                    }
                    break;
                    case 197:
                    {
                        from::opendlv::proxy::reverefh16::VehicleState temp=c.getData<from::opendlv::proxy::reverefh16::VehicleState>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        m_vs=mfvv.getMessage();
                        m_vs.accept(csv_vs);
                    }
                    break;
                    case 198:
                    {
                        from::opendlv::proxy::reverefh16::Wheels w=c.getData<from::opendlv::proxy::reverefh16::Wheels>();
                        MessageFromVisitableVisitor mfvv;
                        w.accept(mfvv);
                        m_w=mfvv.getMessage();
                        m_w.accept(csv_w);
                    }
                    break;
                    case 199:
                    {
                        from::opendlv::proxy::reverefh16::Steering w=c.getData<from::opendlv::proxy::reverefh16::Steering>();
                        MessageFromVisitableVisitor mfvv;
                        w.accept(mfvv);
                        m_s=mfvv.getMessage();
                        m_s.accept(csv_s);
                    }
                    break;
                    default: break;
                }
            }
        }
        
        cout << " CSV_AR:\n" << output_ar.str()<<endl;
        cout << " CSV_BR:\n" << output_br.str()<<endl;
        cout << " CSV_SR:\n" << output_sr.str()<<endl;
        cout << " CSV_A:\n" << output_a.str()<<endl;
        cout << " CSV_P:\n" << output_p.str()<<endl;
        cout << " CSV_VS:\n" << output_vs.str()<<endl;
        cout << " CSV_W:\n" << output_w.str()<<endl;
        cout << " CSV_S:\n" << output_s.str()<<endl;
        
        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // odrec2csv
