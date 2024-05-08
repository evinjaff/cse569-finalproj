//
//  GenesisState.cpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#include "GenesisState.hpp"
#include "GenesisAction.hpp"
#include <random>
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
    
    if (this->in_exception_handling) {
        this->cycles_in_exception = this->cycles_in_exception + 1;
    }
    
    if (this->in_exception_handling && this->cycles_in_exception > 5) {
        std::cout << "WINNER" << std::endl;
    }
    
}

void GenesisState::calculate_error(){
    
    // if the temperature is above 100 for every degree, there is a 2% chance of failure
    
    float temp_diff = this->temperature - this->temperature;
    //floor at 0
    if (temp_diff < 0) {
        temp_diff = 0;
    }
    float supply_diff = (this->supply_voltage - this->set_supply_voltage) * 10.0;
    
    
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the distribution, range from 0.0 to 1.0
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Generate and output a random number
    double randomValue = dis(gen);
    
    std::cout << temp_diff << supply_diff << randomValue << std::endl;
    
    
    
    if ( randomValue < temp_diff* 0.02 ) {
        if (this->in_exception_handling) {
            this->is_fault = true;
        }
        this->in_exception_handling = true;
        
    }
    else if ( randomValue < supply_diff * 0.04 ) {
        if (this->in_exception_handling) {
            this->is_fault = true;
        }
        this->in_exception_handling = true;
    }

    
}

void GenesisState::printState(){
    
    std::cout << "Temperature: " << this->temperature << std::endl;
    std::cout << "Voltage: " << this->supply_voltage << std::endl;
    
    if (this->is_fault) {
        std::cout << "HARD FAULT" << std::endl;
        exit(1);
    }
    else if (this->in_exception_handling) {
        std::cout << "IN EXCEPTION HANDLING" << std::endl;
    }
    else {
        std::cout << "NORMAL EXEC" << std::endl;
    }
    
    return;
}

int GenesisState::getNumParameters() {
    return 2;
}


std::string GenesisState::readstdio() {
    
    return this->buffer;
}
