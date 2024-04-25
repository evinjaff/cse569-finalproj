//
//  GenesisState.hpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#ifndef GenesisState_hpp
#define GenesisState_hpp

//#include <stdio.h>
#include "../LLMfuzzer/State.hpp"
#include "../LLMfuzzer/Action.hpp"
#include <string.h>

#endif /* GenesisState_hpp */

class GenesisState : public AbstractState {
    
    public:
    
    GenesisState();
    
    GenesisState(GenesisState& t);
    
    // Variables
    char * RAM [4096];
    float temperature = 69.6;
    float supply_voltage = 3.3;
    
    std::string buffer = "Empty so far";
    
    float set_temperature = 69.6;
    float set_supply_voltage = 3.3;
    
    //Virtual Overrides
    AbstractState * advanceState(AbstractAction) override;
    
    void updateState(float temp, float supply_voltage);
    
    std::string readstdio() override;
    
private:
    
    void calculate_error();
    
    //Helpers
    
};
