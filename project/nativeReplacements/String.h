#pragma once
#include <string>
#include <iterator>

class String: public std::string {
    public:
    String(const char* str): std::string(str) {};
    String(std::string& str): std::string(str) {};
    String(float f): std::string(std::to_string(f)) {};
    String(int f): std::string(std::to_string(f)) {};
    String() {};
    ~String() {};
    bool equals(String& other) { return *this == other;}
    bool equals(const String& other) { return *this == other;}
    int toInt() {
        return std::stoi(*this);
    }
    float toFloat() {
        return std::stof(*this);
    }

    size_t write(u_int8_t c) {
        this->push_back(c);
        return 1;
    }

    size_t write(const u_int8_t* s, size_t n) {
        for (size_t i = 0; i < n; i++)
        {
            this->push_back(s[i]);
        }
        return n;
    }

    friend class HTTPClient;
};