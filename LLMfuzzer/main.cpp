//
//  main.cpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#include <iostream>
#include <vector>
#include "../GenesisCase/GenesisState.hpp"
#include "openai.hpp"
#include "../Utils/openai_assistant.hpp"
#include "../Utils/openai-gpt4.hpp"
#include "../json/json.h"


std::vector<float> extractNumbers(const std::string& jsonString) {
    Json::Value root;
    Json::Reader reader;
    std::vector<float> numbers;

    // Parse the JSON string
    bool parsingSuccessful = reader.parse(jsonString, root);
    if (!parsingSuccessful) {
        std::cerr << "Failed to parse JSON: " << reader.getFormattedErrorMessages();
    }

    // Extract the content string
    std::string content = root["choices"][0]["message"]["content"].asString();

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
    
    std::string url = "https://evinjaff.github.io/donate.txt";
    
    std::string apiKey = "sk-";
//    OpenAI_Assistant assistant(apiKey);
//    assistant.start_conversation("carol");
    
    // Replace "YOUR_API_KEY_HERE" with your actual OpenAI API key
    OpenAI_GPT gpt(apiKey);

    // Prepare a vector of messages representing the conversation
    std::vector<std::string> messages = {
        "Hello, you are a hardware fuzzing agent who is an expert in fuzzing systems. Your target is a Sega Genesis where you want to trigger an exception. You are allowed to make two physical changes, you can turn the temperature up or down by 15 degrees F or decrease the supply voltage up or down by .3 volts. Reply in two numbers, the amount to modify the temperature and the amount to modify the supply voltage",
    };

    // Send messages to GPT-4 and receive the chat completion
    std::string response = gpt.chat(messages);

    std::cout << "Response from GPT-4: " << response << std::endl;
    
    std::vector<float> numbers = extractNumbers(response);
    if (!numbers.empty()) {
        std::cout << "Extracted numbers are: a = " << numbers[0] << ", b = " << numbers[1] << std::endl;
        
        float temp = numbers[0];
        float voltage = numbers[1];
        
        state->updateState(temp, voltage);
        
        std::cout << state->readstdio() << std::endl;
        
        
    } else {
        std::cout << "No numbers extracted." << std::endl;
    }
    
    


}
