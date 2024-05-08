//
//  State.hpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#ifndef State_hpp
#define State_hpp
#endif /* State_hpp */

//#include <stdio.h>
#include <string>
#include "Action.hpp"

#pragma once


class AbstractState {
    
    public:
        
        virtual std::string readstdio() = 0;
        
        // Main function to advance the state based on an abstract action
        virtual AbstractState * advanceState(AbstractAction) = 0;
    
        virtual void printState() = 0;
        
        virtual int getNumParameters() = 0;
    
};
