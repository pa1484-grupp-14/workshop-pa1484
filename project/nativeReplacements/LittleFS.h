#pragma once
#include "String.h"
#include <fstream>
#include <filesystem>
#include <string>
#define FILE_WRITE 1
class File {
    private:
    std::fstream** file_stream;
    public:
    ~File() {
        if(file_stream != nullptr) {  
            (*file_stream)->close();
            delete *file_stream;
            delete file_stream;
        }
    }
    File(): file_stream(nullptr) {}
    File(const char* path): file_stream(new (std::fstream*)(new std::fstream(path)) ) {

    } 
    File& operator=(const File& other) {
        (*file_stream)->close();
        delete file_stream;
        file_stream = other.file_stream;
        *other.file_stream = nullptr;
        return *this;
    }
    bool isDirectory() { return false; };
    String readString() { return ""; };
    File openNextFile() { return File(); };
    char* name() { return ""; };
    char* path() { return ""; };
    int size() {
        return 0;
    }
    void close() {
        if(file_stream != nullptr) {  
            (*file_stream)->close();
            delete *file_stream;
            delete file_stream;
        }
    }
    bool print(const char* path) { return false; }
    bool valid();
    bool operator!() { return file_stream != nullptr;}

};
namespace fs {
    class FS {
        private:
        public:
        bool mkdir(const char* path) {
            return std::filesystem::create_directory("." + std::string(path));
        }
        bool rmdir(const char* path) {
            return std::filesystem::remove_all("." + std::string(path));
        }
        File open(const char* path, int open = 0) {
            return File(path);
        }
        int WriteFile(const char* path) { return 0;};
        bool exists(const char* path) { return std::filesystem::exists(path);}
        bool begin(bool = false) {return true;}
    };

}
static fs::FS LittleFS;
