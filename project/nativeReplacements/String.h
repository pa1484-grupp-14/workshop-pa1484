#pragma once
#include <string>
#include <iterator>
#include <cstddef>
#ifdef NATIVE_BUILD
bool strstr(const std::string& a, const std::string& b );
class String {
    private:
    std::string data;
    public:


    struct Iterator 
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = char;
        using pointer           = char*;
        using reference         = char&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }  
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };  

    private:
        pointer m_ptr;
    };


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
    bool operator==(String& other) {return this->data == other.data;}
    bool operator==(const String& other) {return this->data == other.data;}
    int toInt() {
        return std::stoi(data);
    }
    float toFloat() {
        return std::stof(data);
    }
    friend class HTTPClient;
};
#endif