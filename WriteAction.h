// WriteAction.h
//  SugarScape
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
#ifndef __SugarScape__WriteAction__
#define __SugarScape__WriteAction__
//includes:
#include <iostream>
#include "Action.h"
#include <omp.h>

/*!  \class  WriteAction All Write-Dependent Actions inherit from this
 \brief Contains algorithm for executing Write-Dependent actions
 Inherit from this and implement executeAction and formGroup
 */
class WriteAction:public Action{
public:
    WriteAction(World*);
    virtual ~WriteAction();
    virtual bool run(int,int,int);
    virtual bool concurrentRun(void);
    virtual int participantCount(int,int,int);
    virtual int pickIndex(std::vector<Location*>);
};
#endif /* defined(__SugarScape__WriteAction__) */