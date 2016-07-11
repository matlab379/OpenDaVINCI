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

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include "opendavinci/generated/odcore/data/SharedPointCloud.h"
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/io/conference/ContainerConference.h>
#include "opendavinci/odcore/base/Lock.h"
#include "csvToSPC.h"

namespace automotive {

        using namespace std;

        csvToSPC::csvToSPC(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "csvToSPC"),
            lidarData(),
            m_velodyneSharedMemory(odcore::wrapper::SharedMemoryFactory::createSharedMemory(NAME, SIZE)),
            m_spc(),
            stop(){}

        csvToSPC::~csvToSPC() {}

        void csvToSPC::setUp() {
            lidarData.open("LidarSensorData.csv");
        }

        void csvToSPC::tearDown() {
            lidarData.close();
        }

        // This method will do the main data processing job.
        //Running this module with a frequency of 60Hz gives a data rate 3*10⁶Bps
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode csvToSPC::body() {
            string value;
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING){
                vector<float> xyValues;
                if(getline(lidarData,value) && !stop){
                    stringstream lineStream(value);
                    string cell;
                    int counter=0;
                    while(getline(lineStream,cell,',')){
                        if(counter%4==2 || counter%4==3){
                            xyValues.push_back(stof(cell));
                        }
                        counter++;
                    }
                    cout<<counter<<endl;
                    cout<<xyValues.size()<<endl;
                
                    if(m_velodyneSharedMemory->isValid()){
                        uint32_t startID = 0;
                        // Using a scoped lock to lock and automatically unlock a shared memory segment.
                        odcore::base::Lock l(m_velodyneSharedMemory);
                        float *velodyneRawData = static_cast<float*>(m_velodyneSharedMemory->getSharedMemory());
                        for(uint32_t j = 0;j<xyValues.size();j += 2){
                            velodyneRawData[startID] = xyValues[j];
                            velodyneRawData[startID + 1] = xyValues[j+1];
                            velodyneRawData[startID + 2] = 1.0;
                            velodyneRawData[startID + 3] = 0.5;
                            startID += 4;
                        }
                    }
                    
                    xyValues.clear();
                      
                    m_spc.setName(m_velodyneSharedMemory->getName()); // Name of the shared memory segment with the data.
                    m_spc.setSize(SIZE); // Size in raw bytes.
                    m_spc.setWidth(POINT_SIZE); // Number of points.
                    m_spc.setHeight(1); // We have just a sequence of vectors.
                    m_spc.setNumberOfComponentsPerPoint(NUMBER_OF_COMPONENTS_PER_POINT);
                    m_spc.setComponentDataType(odcore::data::SharedPointCloud::FLOAT_T); // Data type per component.
                    m_spc.setUserInfo(odcore::data::SharedPointCloud::XYZ_INTENSITY);
                  
                    odcore::data::Container imageFrame(m_spc);
                    getConference().send(imageFrame);
                } 
                else{
                    if(!stop){
                        lidarData.close();
                        stop=true;
                    }
                }  
            }
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
} // automotive

