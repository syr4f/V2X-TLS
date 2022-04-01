//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "veins/modules/application/traci/TraCIDemoEV.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::TraCIDemoEV);

void TraCIDemoEV::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {

        mobility = TraCIMobilityAccess().get(getParentModule());
        //traci = mobility->getCommandInterface();
        traciVehicle = mobility->getVehicleCommandInterface();
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }

}


void TraCIDemoEV::handleSelfMsg(cMessage* msg)
{
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(msg)) {
        // send this message on the service channel until the counter is 3 or higher.
        // this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 1) { //normally 3
            // stop service advertisements
            stopService();
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    }
    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void TraCIDemoEV::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    std::string carType = traciVehicle->getTypeId();
    std::string laneId = traciVehicle->getLaneId();
    double carLoc = traciVehicle->getDistanceTravelled();
    double carSpeed = traciVehicle->getSpeed();
    std::string routeId = traciVehicle->getRouteId().c_str();

         if(carType == "emergency"){
             findHost()->getDisplayString().setTagArg("i", 1, "red");

              }

         if(carType == "emergency"){

             if(laneId == "14617022#0_0" || laneId == "163897622#3_0" || laneId == "23092613#4_1" || laneId == "23092613#4_0" || laneId == "399684423#2_1" || laneId == "399684423#2_0"){
             TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage();
             populateWSM(wsm);
             wsm->setDemoData(traciVehicle->getLaneId().c_str());
             sendDown(wsm);
             }
             }


             else {
             lastDroveAt = simTime();
             }
         }


