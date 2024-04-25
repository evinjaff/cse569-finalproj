//
//  openai-gpt4.cpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/25/24.
//

#include "openai-gpt4.hpp"
#include <iostream>
#include <sstream>
#include "../json/json.h"  // Make sure to include a library to handle JSON

// Constructor
OpenAI_GPT::OpenAI_GPT(const std::string& key) : apiKey(key), curl(curl_easy_init()), headers(NULL) {
    if (curl) {
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string authHeader = "Authorization: Bearer " + apiKey;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    }
}

// Destructor
OpenAI_GPT::~OpenAI_GPT() {
    if (headers) {
        curl_slist_free_all(headers);
    }
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

// Callback function to capture the response from cURL request
size_t OpenAI_GPT::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch(std::bad_alloc &e) {
        return 0; // handle memory problem
    }
    return newLength;
}

// Send messages to GPT-4 chat and get the response
std::string OpenAI_GPT::chat(const std::vector<std::string>& messages) {
    Json::Value root;
    Json::StreamWriterBuilder builder;
    Json::Value messageArray(Json::arrayValue);

    for (const auto& msg : messages) {
        Json::Value messageObj;
        messageObj["role"] = "user";
        messageObj["content"] = msg;
        messageArray.append(messageObj);
    }

    root["model"] = "gpt-4";
    root["messages"] = messageArray;

    std::string postData = Json::writeString(builder, root);

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return "";
    }

    return readBuffer;
}
