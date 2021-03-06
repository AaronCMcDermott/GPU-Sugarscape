//  main.cpp
//  SugarScape
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//
// Disclaimer:
// ----------
// This code will work only if you selected window, graphics and audio.
// Note that the "Run Script" build phase (XCode) will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cuda.h>
#include <iostream>
#include <fstream>
#include <omp.h>
#include "World.h"
#include "Growback.h"
#include "SeasonalGrowback.h"
#include "PollutionFormation.h"
#include "GarbageCollection.h"
#include "AgentMove.h"
#include "AgentCulture.h"
#include "AgentDeath.h"
#include "AgentDisease.h"
#include "Diffusion.h"
#include "AgentCombat.h"
#include "AgentReplacement.h"
#include "AgentMetabolism.h"
#include "AgentMating.h"
#include "AgentLoanPayments.h"
#include "AgentCredit.h"
#include "ViewPort.h"

int benchmark(int,int,int,int,int,std::string);
int Gui(int, float);
int Gui(int Dimensions, float pause)
{
    omp_set_num_threads(8);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML window");
    // create everything
    World theWorld(Dimensions);
    theWorld.init();
    theWorld.sync();
    theWorld.sanityCeck();
    ViewPort theGUI(&window,&theWorld,std::pair<int,int>(1024, 768),std::pair<int,int>(0,0),theWorld.getSize());
    Growback growback(&theWorld);
    SeasonalGrowback seasonalGrowback(&theWorld);
    PollutionFormation pollForm(&theWorld);
    Diffusion diffusion(&theWorld);
    AgentMove move(&theWorld);
    AgentMating agentMating(&theWorld);
    AgentCombat agentCombat(&theWorld);
    AgentCulture agentCulture(&theWorld);
    AgentDisease agentDisease(&theWorld);
    AgentReplacement agentReplacement(&theWorld);
    AgentMetabolism agentMetabolism(&theWorld);
    AgentDeath agentDeath(&theWorld);
    AgentCredit agentCredit(&theWorld);
    AgentLoanPayments agentLoanPayments(&theWorld);
    GarbageCollection gc(&theWorld);
    //!
    /*!
     Add the rules we are using here.
     */
    theWorld.addRule(&growback);
    //theWorld.addRule(&seasonalGrowback);
    //theWorld.addRule(&pollForm);
    theWorld.addRule(&diffusion);
    theWorld.addRule(&move);
    theWorld.addRule(&agentMating);
    //theWorld.addRule(&agentCombat);
    theWorld.addRule(&agentCulture);
    theWorld.addRule(&agentDisease);
    //theWorld.addRule(&agentReplacement);
    theWorld.addRule(&agentMetabolism);
    theWorld.addRule(&agentDeath);
    //theWorld.addRule(&gc);
    //theWorld.addRule(&agentCredit);
    //theWorld.addRule(&agentLoanPayments);

    int stepCount=0;
    std::string counter;
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("resources/icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf")) {
        return EXIT_FAILURE;
    }
    counter = std::to_string(stepCount);
    sf::Text text(counter, font, 50);
    text.setColor(sf::Color::White);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("resources/nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music -it never hurts!
    music.play();
    //!
    /*!
     set number of threads here - for testing only. Not needed normally
     */
    omp_set_num_threads(8);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();
        theWorld.applyRules();
        theGUI.draw();
        // Draw the sprite
        //window.draw(sprite);
        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
        counter = std::to_string(++stepCount);
        text.setString(counter);
        sf::Time t1 = sf::seconds(pause);
        sf::sleep(t1);
        theWorld.sanityCeck();
    }
    return stepCount;
}


int benchmark(int numRepeats, int stepCount, int dimStart, int increment, int runs, std::string fileName){
    std::ofstream outputFile(fileName,std::ios::out | std::ios::app);
    omp_set_num_threads(8);
    for (int i=0; i<runs; ++i) {
        std::chrono::duration <double, std::milli> min;
        std::chrono::duration <double, std::milli> max;
        for (int k=0;k<numRepeats; ++k) {
            // create everything
            std::cout << "SIZE" << dimStart+i*increment << ": ";
            outputFile  << dimStart+i*increment << ",";
            World theWorld(dimStart+i*increment);
            theWorld.init();
            theWorld.sync();
            //theWorld.sanityCeck();
            Growback growback(&theWorld);
            //SeasonalGrowback seasonalGrowback(&theWorld);
            PollutionFormation pollForm(&theWorld);
            Diffusion diffusion(&theWorld);
            AgentMove move(&theWorld);
            AgentMating agentMating(&theWorld);
            AgentCombat agentCombat(&theWorld);
            //AgentCulture agentCulture(&theWorld);
            AgentDisease agentDisease(&theWorld);
            //AgentReplacement agentReplacement(&theWorld);
            AgentMetabolism agentMetabolism(&theWorld);
            AgentDeath agentDeath(&theWorld);
            AgentCredit agentCredit(&theWorld);
            AgentLoanPayments agentLoanPayments(&theWorld);
            //GarbageCollection gc(&theWorld);
            //!

            /*!
             Add the rules we are using here.
             */
            theWorld.addRule(&growback);
            //theWorld.addRule(&seasonalGrowback);
            //theWorld.addRule(&pollForm);
            theWorld.addRule(&diffusion);
            theWorld.addRule(&move);
            theWorld.addRule(&agentMating);
            //theWorld.addRule(&agentCombat);
            //theWorld.addRule(&agentCulture);
            theWorld.addRule(&agentDisease);
            //theWorld.addRule(&agentReplacement);
            theWorld.addRule(&agentMetabolism);
            theWorld.addRule(&agentDeath);
            //theWorld.addRule(&gc);
            //theWorld.addRule(&agentCredit);
            //theWorld.addRule(&agentLoanPayments);

            omp_set_num_threads(8);

            auto start = std::chrono::steady_clock::now();
            for (int m=0; m<stepCount; ++m) {
                //step
                theWorld.applyRules();
            }
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            if (k==0) {
                min=max=diff;
            }else{
                if (diff<min) min=diff;
                else if (diff>max) max=diff;
            }
            std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms ";
            std::cout  << std::chrono::duration <double, std::nano> (diff).count() << " ns " ;
            std::cout << "Agents:" << theWorld.getAgentCount() <<std::endl;
            outputFile  << std::chrono::duration <double, std::milli> (diff).count() << ",";
            outputFile  << std::chrono::duration <double, std::nano> (diff).count() << ","
            << theWorld.getAgentCount() <<std::endl;
        }
        std::cout << "MIN:" << std::chrono::duration <double, std::milli> (min).count()
        <<" MAX:" << std::chrono::duration <double, std::milli> (max).count()
        << std::endl;
    }
    outputFile.close();
    return 0;
}

int main(int, char const**)
{
    Gui(30,1.0);
    benchmark(10,50, 10, 10, 10, "/home/aaroncmcd/Documents/Benchmark/A/tester.txt");
    //no of instances,-,starting point,increase,no of runs
    return EXIT_SUCCESS;
}