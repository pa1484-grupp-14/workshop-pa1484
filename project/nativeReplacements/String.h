#pragma once
#include <string>

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
    inline const char* c_str() {return data.c_str();}
    bool equals(String& other) { return this->data == other.data;}
    bool equals(const String& other) { return this->data == other.data;}
    String operator+(String& other) { return String(this->data + other.data);}
    String operator+(String other) { return String(this->data + other.data);}
    String operator+(char* other) { return String(this->data + std::string(other));}
    String operator+(const char* other) { return String(this->data + std::string(other));}
    void operator+=(String other) {this->data += other.data;}
    friend class HTTPClient;
};