//  AgentCulture.cpp
//  SugarScape
//  Created by Joseph Kehoe on 12/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
#include "AgentCulture.h"

AgentCulture::AgentCulture(World *s):ReadAction(s){
    //EMPTY
}
/**
 * If location contains an agent then apply culture rule to that agent
 * @param loc :location to be checked
 * @see Culture Rule
 * @return true if location contained agent else false
 * @exception none
 */
bool AgentCulture::executeAction(Location *loc, group* ) {
    //offloads to intel MIC (experiment)
    //will only work with intel devices with Xeon Phi
#pragma offload target(mic:0)
    {
        if (loc->hasAgent()) {
            std::vector<Agent *> neighbours = sim->getNeighbours(loc->getPosition(), 1);
            for (auto a:neighbours) {
                std::vector<bool> tags = a->getCulture();
                int index = sim->getRnd(0, sim->getCultureCount() - 1);
                loc->getAgent()->setTag(index, tags[index]);
            }
            return true;
        } else {
            return false;
        }
    }
}