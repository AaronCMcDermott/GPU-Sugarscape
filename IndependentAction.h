// IndependentAction.h
//  SugarScape
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
#ifndef __SugarScape__IndependentAction__
#define __SugarScape__IndependentAction__
//includes:
#include <iostream>
#include "Action.h"
#include <SFML/Graphics.hpp>
#include <omp.h>
#include <cuda.h>
#include <cudaProfiler.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
/*!  \class  IndependentAction
 \brief Actions that require no interaction between agents
 The simplest possible agent actions.  No interaction between agents. Every agent acts independently.
 */
class IndependentAction:public Action{
public:
    IndependentAction(World*);
    virtual ~IndependentAction();
    virtual bool run(int,int,int);
    virtual bool concurrentRun(void);
    virtual group* formGroup(Location*);
};
#endif /* defined(__SugarScape__IndependentAction__) */