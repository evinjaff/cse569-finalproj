//
//  GenesisAction.hpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#ifndef GenesisAction_hpp
#define GenesisAction_hpp

//#include <stdio.h>
#include "../LLMfuzzer/State.hpp"
#include "../LLMfuzzer/Action.hpp"

#endif /* GenesisAction_hpp */

class GenesisAction : public AbstractAction {
    
    public:
    // Variables
    float supply_voltage = 3.3;
    float temperature = 69.6;
    
    GenesisAction(float supply_voltage, float temperature);
    
    
    
    //Virtual Overrides
    void getIdentifier();
    
    
    //Helpers
    
};
