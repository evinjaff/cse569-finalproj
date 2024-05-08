//
//  main.cpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#include <iostream>
#include <vector>
#include "../GenesisCase/GenesisState.hpp"
#include "../Utils/openai.hpp"
#include "../Utils/openai_assistant.hpp"
#include "../Utils/openai-gpt4.hpp"
#include "../json/json.h"


std::vector<float> extractNumbers(const std::string& jsonString, bool is_json) {
    Json::Value root;
    Json::Reader reader;
    std::vector<float> numbers;
    
    std::string content;
    
    if(is_json){
        // Parse the JSON string
        bool parsingSuccessful = reader.parse(jsonString, root);
        if (!parsingSuccessful) {
            std::cerr << "Failed to parse JSON: " << reader.getFormattedErrorMessages();
        }
        
        // Extract the content string
        content = root["choices"][0]["message"]["content"].asString();
    }
    else {
        content = jsonString;
    }
    std::cout << "extracting from: " << content << std::endl;
    // Use stringstream to extract numbers from the content string
    std::stringstream ss(content);
    float a, b;
    ss >> a >> b;  // Assume the content format correctly contains two floats
    
    numbers.push_back(a);
    numbers.push_back(b);


    return numbers;
}



int main() {
    
    
    // Genesis Example
    GenesisState * state = new GenesisState();
    
    std::string key = "blank";
    OpenAI_Assistant LLM = OpenAI_Assistant(key);
    
    for(unsigned int i = 0; i<20;i++){
        
        std::string llm_result = LLM.offline_call(state, state->getNumParameters());
        
        std::cout << llm_result << std::endl;
        
        std::vector<float> numbers = extractNumbers(llm_result, false);
    
        if (!numbers.empty()) {
            std::cout << "Extracted numbers are: a = " << numbers[0] << ", b = " << numbers[1] << std::endl;
            
            float temp = numbers[0];
            float voltage = numbers[1];
            
            state->updateState(temp, voltage);
            
            std::cout << state->readstdio() << std::endl;
            
        }
        
    }

    
    
    
    
    
//    std::cout << "Response from GPT-4: " << response << std::endl;
//    

//        
//    } else {
//        std::cout << "No numbers extracted." << std::endl;
//    }
//    
    


}
