
#include <string>

#define HTTP_CODE_OK 200
class String {
    private:
    std::string data;
    public:
    String(const char* str): data(str) {};
    String(std::string str): data(str) {};
    String(float f): data(std::to_string(f)) {};
    String() {};
    ~String() {};
    String operator+(String& other) { return String(this->data + other.data);}
    String operator+(String other) { return String(this->data + other.data);}
    String operator+(char* other) { return String(this->data + std::string(other));}
    String operator+(const char* other) { return String(this->data + std::string(other));}
    void operator+=(String other) {this->data += other.data;}

};

class WiFiClient {
    private:
    std::string dummy_data;
    public:
    int read() { return 67;}
};
class HTTPClient {
    private:
    WiFiClient* dummy;
    String url;
    public:
    bool begin(WiFiClient& client, String url) {
        this->url = url;
        this->dummy = &client;
        return true;
    }
    void end() {
        
    }
    int GET() {
        return 200;
    }
    WiFiClient* getStreamPtr() {
        return dummy;
    }
};
