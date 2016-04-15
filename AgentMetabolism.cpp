//  AgentMetabolism.cpp
//  SScapeGUI
//  Created by Joseph Kehoe on 26/08/2015.
//  Copyright (c) 2015 Joseph Kehoe. All rights reserved.
#include "AgentMetabolism.h"
AgentMetabolism::AgentMetabolism(World *sim):IndependentAction(sim) {
}
/**
 * Decrements an agents sugar by their metabolism
 * @param loc :Location in lattice we are running action on
 * @param group pointer not used - nullptr passed in
 * @see Metabolism in book
 * @return true if agent was at location else false
 * @exception none
 */
bool AgentMetabolism::executeAction(Location * loc, group * ){
    //offloads to intel MIC (experiment)
    //will only work with intel devices with Xeon Phi
#pragma offload target(mic:0)
    {
//run once on single thread
#pragma omp critical
        if (loc->hasAgent()) {
            Agent *agent = loc->getAgent();
            agent->incSugar(-agent->getMetabolism());
            agent->incAge();
        }
        return true;
    }
}