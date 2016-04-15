// GarbageCollection.h
//  SugarScape
//  Created by Joseph kehoe on 16/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
#ifndef __SugarScape__GarbageCollection__
#define __SugarScape__GarbageCollection__
//includes:
#include <iostream>
#include "IndependentAction.h"
#include <SFML/Graphics.hpp>
#include <omp.h>
/*!  \class  GarbageCollection
 \brief Deletes pointers to agents that are dead
 Location holds pointers to dead agents.  This just deletes those agents pointed to.
 The other rules death, replacement, etc. populate this pointer as required
 */
class GarbageCollection:public IndependentAction{
public:
    GarbageCollection(World *s);
    virtual bool executeAction(Location *, group *);
};
#endif /* defined(__SugarScape__GarbageCollection__) */