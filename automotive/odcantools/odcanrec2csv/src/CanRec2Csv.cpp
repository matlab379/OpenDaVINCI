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
#include <fstream>

#include "CanRec2Csv.h"
#include "opendavinci/odcore/reflection/Message.h"
#include "opendavinci/odcore/reflection/MessageFromVisitableVisitor.h"

#include "automotivedata/generated/from/opendlv/proxy/reverefh16/Pedals.h"
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
    using namespace odcore::data;

    Rec2csv::Rec2csv(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odcanrec2csv"),
        m_fifo() {
        
        for(int i=0;i<MAX_CSVs;++i) m_csvs[i]=NULL;
        for(int i=0;i<MAX_CSVs;++i) m_csv_files[i]=NULL;
    }

    Rec2csv::~Rec2csv() {}

    void Rec2csv::setUp() {}

    void Rec2csv::tearDown() {
        for(int i=0;i<MAX_CSVs;++i)
            if(m_csvs[i]!=NULL)
                delete m_csvs[i];
                
        for(int i=0;i<MAX_CSVs;++i)
            if(m_csv_files[i]!=NULL && m_csv_files[i]->is_open())
                    m_csv_files[i]->close();
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Rec2csv::body() {
        addDataStoreFor(m_fifo);
        
        stringstream outputs[MAX_CSVs];
        for(int i=0;i<MAX_CSVs;++i)
            m_csvs[i]=new CSVFromVisitableVisitor(outputs[i],true,',');
        Message message[MAX_CSVs];
        int ids[MAX_CSVs];
        for(int i=0;i<MAX_CSVs;++i)
            ids[i]=-1;
        
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
            while (!m_fifo.isEmpty()) {
                Container c = m_fifo.leave();
                
                CLOG2 << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() << "-->" << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() << " dt = " << (c.getReceivedTimeStamp() - c.getSentTimeStamp()).toString() << " ID = " << c.getDataType() << endl; 
                
                
//message from.opendlv.proxy.reverefh16.ManualControl [id = 191]
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
                    case 191:
                    {
                        from::opendlv::proxy::reverefh16::Pedals temp=c.getData<from::opendlv::proxy::reverefh16::Pedals>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        message[0]=mfvv.getMessage();
                        message[0].accept(*m_csvs[0]);
                        ids[0]=191;
                    }
                    break;
                    case 192:
                    {
                        from::opendlv::proxy::reverefh16::AccelerationRequest temp=c.getData<from::opendlv::proxy::reverefh16::AccelerationRequest>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        message[1]=mfvv.getMessage();
                        message[1].accept(*m_csvs[1]);
                        ids[1]=192;
                    }
                    break;
                    case 193:
                    {
                        from::opendlv::proxy::reverefh16::BrakeRequest temp=c.getData<from::opendlv::proxy::reverefh16::BrakeRequest>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        message[2]=mfvv.getMessage();
                        message[2].accept(*m_csvs[2]);
                        ids[2]=193;
                    }
                    break;
                    case 194:
                    {
                        from::opendlv::proxy::reverefh16::SteeringRequest temp=c.getData<from::opendlv::proxy::reverefh16::SteeringRequest>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        message[3]=mfvv.getMessage();
                        message[3].accept(*m_csvs[3]);
                        ids[3]=194;
                    }
                    break;
                    case 195:
                    {
                        from::opendlv::proxy::reverefh16::Axles temp=c.getData<from::opendlv::proxy::reverefh16::Axles>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        message[4]=mfvv.getMessage();
                        message[4].accept(*m_csvs[4]);
                        ids[4]=195;
                    }
                    break;
                    case 196:
                    {
                        from::opendlv::proxy::reverefh16::Propulsion temp=c.getData<from::opendlv::proxy::reverefh16::Propulsion>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        message[5]=mfvv.getMessage();
                        message[5].accept(*m_csvs[5]);
                        ids[5]=196;
                    }
                    break;
                    case 197:
                    {
                        from::opendlv::proxy::reverefh16::VehicleState temp=c.getData<from::opendlv::proxy::reverefh16::VehicleState>();
                        MessageFromVisitableVisitor mfvv;
                        temp.accept(mfvv);
                        message[6]=mfvv.getMessage();
                        message[6].accept(*m_csvs[6]);
                        ids[6]=197;
                    }
                    break;
                    case 198:
                    {
                        from::opendlv::proxy::reverefh16::Wheels w=c.getData<from::opendlv::proxy::reverefh16::Wheels>();
                        MessageFromVisitableVisitor mfvv;
                        w.accept(mfvv);
                        message[7]=mfvv.getMessage();
                        message[7].accept(*m_csvs[7]);
                        ids[7]=198;
                    }
                    break;
                    case 199:
                    {
                        from::opendlv::proxy::reverefh16::Steering w=c.getData<from::opendlv::proxy::reverefh16::Steering>();
                        MessageFromVisitableVisitor mfvv;
                        w.accept(mfvv);
                        message[8]=mfvv.getMessage();
                        message[8].accept(*m_csvs[8]);
                        ids[8]=199;
                    }
                    break;
                    default: break;
                }
            }
        }
        
        CLOG2 <<endl<< " CSV_Pedals:\n" << outputs[0].str()<<endl;
        CLOG2 << " CSV_AccelerationRequest:\n" << outputs[1].str()<<endl;
        CLOG2 << " CSV_BrakeRequest:\n" << outputs[2].str()<<endl;
        CLOG2 << " CSV_SteeringRequest:\n" << outputs[3].str()<<endl;
        CLOG2 << " CSV_Axles:\n" << outputs[4].str()<<endl;
        CLOG2 << " CSV_Propulsion:\n" << outputs[5].str()<<endl;
        CLOG2 << " CSV_VehicleState:\n" << outputs[6].str()<<endl;
        CLOG2 << " CSV_Wheels:\n" << outputs[7].str()<<endl;
        CLOG2 << " CSV_Steering:\n" << outputs[8].str()<<endl<<endl;
        
        string filename="", header="CSV_", trailer=".csv";
        
        // print all type identifiers that were identified
        cout << endl << "Identified data types:";
        for(int i=0;i<MAX_CSVs;++i)
            if(ids[i]!=-1)
            {
                cout << " " << ids[i];
                
                // dump result in a csv file
                filename=header+std::to_string(ids[i])+trailer; // C++11
                m_csv_files[i]=new ofstream (filename);
                if(m_csv_files[i]->is_open())
                {
                    *m_csv_files[i] << outputs[i].str();
                    m_csv_files[i]->close();
                }
                else cerr << "Unable to open file " << filename << endl;
            }
        cout<<endl;
        
        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // odrec2csv
