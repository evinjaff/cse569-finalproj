//
//  openai-gpt4.hpp
//  LLMfuzzer
//
//  Created by Evin Jaff on 4/25/24.
//


//#include <stdio.h>
#include <string>
#include <curl/curl.h>

class OpenAI_GPT {
public:
    explicit OpenAI_GPT(const std::string& key);
    ~OpenAI_GPT();

    std::string chat(const std::vector<std::string>& messages);

private:
    std::string apiKey;
    CURL *curl;
    struct curl_slist *headers;

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);
};



