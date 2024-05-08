//
//  openai_assistant.cpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/25/24.
//

#include "openai_assistant.hpp"
//#include ""

// Callback function to capture the response from cURL request
size_t OpenAI_Assistant::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch(std::bad_alloc &e) {
        // handle memory problem
        return 0;
    }
    return newLength;
}


OpenAI_Assistant::OpenAI_Assistant(const std::string& key) : apiKey(key), curl(curl_easy_init()), headers(NULL) {
    if (curl) {
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string authHeader = "Authorization: Bearer " + apiKey;
        headers = curl_slist_append(headers, authHeader.c_str());
        headers = curl_slist_append(headers, "OpenAI-Beta: assistants=v2");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    }
}

OpenAI_Assistant::~OpenAI_Assistant() {
    if (headers) {
        curl_slist_free_all(headers);
    }
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

void OpenAI_Assistant::start_conversation(const std::string& assistantName) {
    if (curl) {
        std::string readBuffer;
        std::string postData = "{\"assistant_id\":\"" + assistantName + "\"}";

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/threads");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Response from OpenAI API: " << readBuffer << std::endl;
        }
    }
}


std::string OpenAI_Assistant::offline_call( AbstractState * GameState, int num_parameters ) {
    
    //AGH we ran out of OpenAPI credits so let's use the playground where it's still free
    GameState->printState();
    
    std::cout << "Sorry for the limitation, please paste the above state into the playground and then type the LLM's response" << std::endl;
    
    std::string readBuffer;
//    std::cin >> readBuffer;
    std::getline(std::cin, readBuffer);
    
    return readBuffer;
    
 
    
}
