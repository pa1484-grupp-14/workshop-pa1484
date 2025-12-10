#pragma once
#include "String.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <iostream>
#define FILE_WRITE 1
class File {
    private:
    std::string filepath;
    std::fstream** file_stream;
    public:
    ~File() {}
    File(): file_stream(nullptr) {}
    File(const char* path): file_stream(new (std::fstream*)(new std::fstream())), filepath(".") {
        filepath.append(path);
        std::cout << "[filesystem] opening " << filepath << std::endl;
        (*file_stream)->open(filepath);
    } 
    File& operator=(const File& other) {
        (*file_stream)->close();
        delete file_stream;
        file_stream = other.file_stream;
        *other.file_stream = nullptr;
        return *this;
    }
    bool isDirectory() { return false; };
    String readString() { 
        if(!valid()) return String("");
        std::stringstream fileContent;
        fileContent << (*file_stream)->rdbuf();
        return String(fileContent.str().c_str()); 
    };
    File openNextFile() { return File(); };
    char* name() { return ""; };
    const char* path() { return filepath.c_str(); };
    int size() {
        return 0;
    }
    void close() {
        if(file_stream != nullptr) {  
            (*file_stream)->close();
            *file_stream = nullptr;
            delete *file_stream;
            file_stream = nullptr;
            delete file_stream;
        }
    }
    bool print(const char* content) { 
        if(!valid()) return false;
        **file_stream << content;
        return true;
    }
    bool valid() {
        if(file_stream == nullptr) {
            std::cout << "[filesystem] bad file stream container pointer" << std::endl;
            return false; }
        if(*file_stream == nullptr) {
            std::cout << "[filesystem] bad file stream pointer" << std::endl;
            return false; }
        if(!(**file_stream).is_open()) {
            std::cout << "[filesystem] tried accessing closed handle" << std::endl;
            return false; }
        return true;
    }
    bool operator!() { return !valid();}

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
        File open(const char* path, int open = 0, bool default_create = 0) {
            return File(path);
        }
        int WriteFile(const char* path) { return 0;};
        bool exists(const char* path) { return std::filesystem::exists(path);}
        bool begin(bool = false) {return true;}
    };

}
static fs::FS LittleFS;
