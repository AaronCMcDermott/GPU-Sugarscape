//  IndependentAction.cpp
//  SugarScape
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
#include "IndependentAction.h"

IndependentAction::IndependentAction(World* theWorld):Action(theWorld){
}
IndependentAction::~IndependentAction(void){
}
/**
 * Forms exclusive Group for Growback- No group involved so returns null pointer
 * @param currLocation :Location to apply rule to
 * @return Pointer to group
 * @exception none
 */
group* IndependentAction::formGroup(Location *currLocation){
    return nullptr;
}
/**
 * Performs action on entire lattice
 * @see Action
 * @return number of actions performed
 * @exception none
 */
bool IndependentAction::run(int startX, int startY, int size){
    Location* Lattice=sim->getLattice();
    int dim=sim->getSize();

    //Perform action

    //offload to target device(GPU),
    //and run in parallel
    //size,dim - read, startX,startY - read/write
#pragma omp target data map(to:i,dim,size) map(tofrom:startX,startY)
#pragma omp parallel for
    for (int i=0; i<size*size; ++i) {
        executeAction(&Lattice[(startX+i/size)*dim+startY+i%size],nullptr);
    }
    //offload to target device(GPU),
    // and run in parallel
    // dim - read,startX,startY - read/write
#pragma omp target device(0) map(to:dim) map(tofrom:startX,startY)
#pragma omp parallel for
    for (int i=startX; i<startX+size; ++i) {
        for (int k=startY; k<startY+size; ++k) {
            executeAction(&Lattice[i*dim+k],nullptr);

        }
    }
    return true;
    //end of offloading
}
//end offloading
/**
 * Performs action on entire lattice concurrently
 * @see Action
 * @return number of actions performed
 * @exception none
 */
bool IndependentAction::concurrentRun(void){
    int size=sim->getSize();
    return run(0,0,size);
}