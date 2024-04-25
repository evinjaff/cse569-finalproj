//
//  GenesisState.cpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#include "GenesisState.hpp"
#include "GenesisAction.hpp"

#include <iostream>

//Constructors
GenesisState::GenesisState() {
    std::cout << "Constructed Genesis State" << std::endl;
};

GenesisState::GenesisState(GenesisState& t) // copy constructor
    {
        std::cout << "Copy Constructor Genesis " << std::endl;
    }



//Virtual Overrides
AbstractState * GenesisState::advanceState(AbstractAction action) {
    
//    newState = new GenesisState(this);
    
    return nullptr;
}

void GenesisState::updateState(float temp, float supply_voltage) {
    
    this->temperature += temp;
    this->supply_voltage += supply_voltage;
    
    this->calculate_error();
    
}

void GenesisState::calculate_error(){
    
    float temp_diff = abs(this->temperature - this->set_temperature);
    float supply_diff = this->supply_voltage - this->set_supply_voltage;
    
    std::cout << temp_diff << " , " << supply_diff << std::endl;
    
    if (temp_diff > 5) {
        this->buffer = "UNHANDLED EXCEPTION";
    }
    if (supply_diff < -0.3) {
        this->buffer = "UNHANDLED EXCEPTION";
    }
    
}


std::string GenesisState::readstdio() {
    
    return this->buffer;
}
