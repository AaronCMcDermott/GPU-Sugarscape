//  Location.h
//  SugarScape
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
#ifndef __SugarScape__Location__
#define __SugarScape__Location__
//includes:
#include <iostream>
#include <algorithm>
#include "Agent.h"
#include "World.h"
#include <omp.h>
#include <SFML/Graphics.hpp>
const std::pair<int, int> nullPosition(-1,-1);
/*!  \class  Location
 \brief Locations of the lattice, representing the world.
 Each location can hold one agent and has Sugar and spice resources.  It can also contain some pollution.
 */
class Location{
    //immutable -- once initialised these stay constant
    std::pair<int,int> position;
    int maxSugar; /*!< Maximum amount of sugar this location may hold at any one time */
    World *sim;/*!< Pointer to the simulation */
    //mutable
    bool done; /*!< True if location has applied current rule successfully */
    int currentSugar,newSugar; /*!< Amount of sugar currently at location */
    int currentPollution,newPollution; /*!< Amount of pollution currently at site */
    Agent *currentResident,*newResident; /*!< Agent currently at this location (if any) */
    Agent *deadAgent;
public:
    //constructors
    Location(World* sim=nullptr, std::pair<int,int> pos=nullPosition);
    //destructor
    ~Location();

    //getters
    bool isDone(void);
    std::pair<int,int> getPosition(void);
    int getX(void);
    int getY(void);
    int getSugar(void);
    int getWealth(void);
    int getReward(void);
    int getMaxSugar(void);
    int getPollution(void);
    Agent* getAgent(void);

    //setters
    std::pair<int,int> setPosition(std::pair<int,int>);
    int setX(int);
    int setY(int);
    int setSugar(int);
    int setMaxSugar(int);
    int setPollution(int);
    Agent *setAgent(Agent*);
    World* setWorld(World*);

    //helpers
    bool markDone(void);
    bool hasAgent(void);
    bool hasDeadAgent(void);
    Location* getCardinal(int);
    Agent* killAgent(void);
    bool putOutGarbage(void);
    bool sync(void);
    bool initAgent(Agent *);
};
#endif /* defined(__SugarScape__Location__) */