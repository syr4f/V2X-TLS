//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
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

#include "veins/modules/application/traci/TraCIRSU.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Define_Module(veins::TraCIRSU);

void TraCIRSU::onWSM(BaseFrame1609_4* frame)
{
    TraCIDemo11pMessage* wsm = check_and_cast<TraCIDemo11pMessage*>(frame);

    manager = TraCIScenarioManagerAccess().get();
    traci = manager->getCommandInterface();

    std:: string laneId = wsm->getDemoData();


//lepaskan yg lane xbyk

    if(laneId == "14617022#0_0" || laneId == "163897622#3_0"){

        //manager->getCommandInterface()->trafficlight("cluster_144084639_252529291_255540900_6503456532").setPhaseIndex(2);
        traci->trafficlight("cluster_144084639_252529291_255540900_6503456532").setPhaseIndex(2);

        }
    else if(laneId == "23092613#4_1" || laneId == "23092613#4_0" || laneId == "399684423#2_1" || laneId == "399684423#2_0"){
        traci->trafficlight("cluster_144084639_252529291_255540900_6503456532").setPhaseIndex(0);
    }
}
