//
//  GenesisAction.cpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#include "GenesisAction.hpp"

#include <iostream>

GenesisAction::GenesisAction(float supply_voltage, float temperature)  // define default constructor            // initialize
{
    this->supply_voltage = supply_voltage;
    this->temperature = temperature;
   //implementation
    std::cout << "GenesisAction Constructor" << std::endl;
}

void GenesisAction::getIdentifier() {
    std::cout << "GenesisAction" << std::endl;
}
