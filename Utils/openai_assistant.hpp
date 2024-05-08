//
//  openai_assistant.hpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/25/24.
//

#include <string>
#include <curl/curl.h>
#include <iostream>
#include "../LLMfuzzer/State.hpp"

class OpenAI_Assistant {
public:
    // Constructor
    explicit OpenAI_Assistant(const std::string& key);
    
    // Destructor
    ~OpenAI_Assistant();
    
    // Starts a conversation with the specified assistant
    void start_conversation(const std::string& assistantName);
    
    std::string offline_call( AbstractState * GameState, int num_parameters );
    
private:
    std::string apiKey; // API key for OpenAI
    CURL *curl;         // cURL handle
    struct curl_slist *headers; // HTTP headers for cURL
    
    // Callback function for writing received data
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);
    
};
