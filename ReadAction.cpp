//  ReadAction.cpp
//  SugarScape
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
#include "ReadAction.h"

ReadAction::ReadAction(World* theWorld):Action(theWorld){
}
ReadAction::~ReadAction(void){
}
/**
 * Forms exclusive Group
 * @param loc :Location to apply rule to
 * @return Pointer to group
 * @exception none
 */
group* ReadAction::formGroup(Location* loc) {
    return nullptr;
}
/**
 * Performs a read only action across entire lattice sequentially
 * @see Action.h
 * @return number of actions performed
 * @exception none
 */
bool ReadAction::run(int startX, int startY, int size){
    Location* Lattice=sim->getLattice();
    int dim=sim->getSize();
    //Perform action

    //offload to target device(GPU),
    // and run in parallel
    // startX,startY,size - read/write
#pragma omp target device(0) map(tofrom:,startX,startY,size)
#pragma omp parallel for
    for (int i=0; i<size*size; ++i) {
        executeAction(&Lattice[(startX+i/size)*dim+startY+i%size],nullptr);
    }
    return true;
}
/**
 * Performs a read only action across entire lattice concurrently
 * @see Action.h
 * @return number of actions performed
 * @exception none
 */
bool ReadAction::concurrentRun(void){
    int size=sim->getSize();
    return run(0,0,size);
}