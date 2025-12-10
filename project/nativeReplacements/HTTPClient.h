#pragma once
#include "prelude.h"
#include <string>
#include <iostream>
#include <fstream>
#include "HTTPRequest.hpp"
#include "String.h"

unsigned long millis();

#define HTTP_CODE_OK 200
class WiFiClient {
    private:
    std::optional<http::Response> response;
    size_t position;
    public:
    int connected() {
        if (response.has_value()) {
            return position < response.value().body.size();
        } else return false;
    }
    size_t readBytes(char *buf, size_t size) {
        return this->read(buf, size);
    }
    int available() {
        if (response.has_value()) {
            int body_len = response.value().body.size();
            if(position < body_len ) return body_len-position;
            else return 0;
        } else return 0;
    }
    int read(char *buf, size_t size)
    {
        int res = -1;
        if (response.has_value()) {
            size_t remainingSize = response.value().body.size()-position;
            res = std::min(remainingSize, size);
            memcpy(buf, &response.value().body[position], res);
            position += res;
        }
        return res;
    }
    void setTimeout(int unused) {}
    int read()
    {
        char data = 0;
        int res = read(&data, 1);
        if(res < 0) {
            return res;
        }
        if (res == 0) {  //  No data available.
            return -1;
        }
        return data;
    }
    friend class HTTPClient;
};
class HTTPClient {
    private:
    WiFiClient* dummy;
    std::optional<http::Request> request;
    public:
    bool begin(WiFiClient& client, String url) {
        this->dummy = &client;
        std::cout << "[HTTPClient::begin]: starting fetch of request:" << std::endl << "[HTTPClient::begin] " << url << std::endl;
        request = std::optional<http::Request>{http::Request(url)};
        return true;
    }
    void end() {
        
    }
    int GET() {
        auto before = millis();
        const auto response = request.value().send("GET");
        auto after = millis();
        std::cout << "[HTTPClient::GET]: responded to request in " << after-before << "ms" << std::endl;
        int code = response.status.code;
        dummy->response = std::optional<http::Response>{response};
        dummy->position = 0;
        return code;
    }
    WiFiClient* getStreamPtr() {
        if(dummy->available() > 0) return dummy;
        else return nullptr;
    }
};