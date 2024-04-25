//
//  openai.hpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/22/24.
//

#ifndef openai_hpp
#define openai_hpp

//#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <iostream>

#endif /* openai_hpp */


namespace OpenAI {

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

void curl_request(std::string * url);

void create_assistant();

void start_thread(std::string * assistant_id);

}
