#include "prelude.h"
#include <string>
#include <iostream>
#include <fstream>
#include "HTTPRequest.hpp"
#define HTTP_CODE_OK 200
class String {
    private:
    std::string data;
    public:
    String(const char* str): data(str) {};
    String(std::string str): data(str) {};
    String(float f): data(std::to_string(f)) {};
    String(int f): data(std::to_string(f)) {};
    String() {};
    ~String() {};
    String operator+(String& other) { return String(this->data + other.data);}
    String operator+(String other) { return String(this->data + other.data);}
    String operator+(char* other) { return String(this->data + std::string(other));}
    String operator+(const char* other) { return String(this->data + std::string(other));}
    void operator+=(String other) {this->data += other.data;}
    friend class HTTPClient;
};

class WiFiClient {
    private:
    std::optional<http::Response> response;
    size_t position;
    public:
    int read(uint8_t *buf, size_t size)
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
    int read()
    {
        uint8_t data = 0;
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
        std::cout << "[HTTPClient::begin]: starting fetch of request." << std::endl;
        request = std::optional<http::Request>{http::Request(url.data)};
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
        return dummy;
    }
};
