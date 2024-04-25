//
//  openai.cpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#include "openai.hpp"

namespace OpenAI {

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void curl_request(std::string * url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url->c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        std::cout << "Evin's Monero Wallet: " << readBuffer << std::endl;
    }
}

void create_assistant() {
    
    
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/assistants");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Initialize a list to hold HTTP headers
        struct curl_slist *headers = NULL;

        // Add headers
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer sk-");
        headers = curl_slist_append(headers, "OpenAI-Beta: assistants=v2");
        
        // Set the headers for the CURL request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        
        res = curl_easy_perform(curl);
        // Clean up the header list
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        std::cout << "Response for Initated Assisant: " << readBuffer << std::endl;
    }
    
}

void create_thread() {
    
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/threads");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Initialize a list to hold HTTP headers
        struct curl_slist *headers = NULL;

        // Add headers
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer sk-");
        headers = curl_slist_append(headers, "OpenAI-Beta: assistants=v2");
        
        // Set the headers for the CURL request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        
        res = curl_easy_perform(curl);
        // Clean up the header list
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        std::cout << "Response for Initated Assisant: " << readBuffer << std::endl;
    }
    
}

void start_thread(std::string * assistant_id) {
    
    create_thread();
    
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/threads/thread_abc123/runs");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Initialize a list to hold HTTP headers
        struct curl_slist *headers = NULL;

        // Add headers
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer sk-");
        headers = curl_slist_append(headers, "OpenAI-Beta: assistants=v2");
        
        std::string post_json = "'{\"role\": \"user\",\n\"content\": \" You are in loop 1 of a fuzzing program, here is the previous state - You can manipulate these 3 fields by these amounts, what would you like to do?\"}'";
        
        std::cout << post_json << std::endl;
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &post_json);
        
        // Set the headers for the CURL request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        
        res = curl_easy_perform(curl);
        // Clean up the header list
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        std::cout << "Response for Initated Assisant: " << readBuffer << std::endl;
    }
    
}

}
