#include "FileHandling.h"
#include <iostream>

#define FORMAT_LITTLEFS_IF_FAILED true 

void FileHandler::listDir(fs::FS& fs, const char* dirname, uint8_t levels) {
  std::cout << "[FileHandler]: Listing directory: " << dirname;

  File root = fs.open(dirname);
  if (!root) {
    std::cout << "- failed to open directory" << std::endl;
    return;
  }
  if (!root.isDirectory()) {
    std::cout << " - not a directory"  << std::endl;
    return;
  }
  std::cout << std::endl;
  File file = root.openNextFile();
  while (!!file) {
    if (file.isDirectory()) {
      std::cout << "  DIR : " << file.name() << std::endl;
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      std::cout << "  FILE: " << file.name() << "\tSIZE: " << file.size() << std::endl;
    }
    file = root.openNextFile();
  }
}

void FileHandler::createDir(fs::FS& fs, const char* path) {
    std::cout << "[FileHandler] Creating Dir: " << path << ", ";
    if (fs.mkdir(path)) {
      std::cout << "Dir created" << std::endl;
    } else {
      std::cout << "mkdir failed" << std::endl;
    }
}

void FileHandler::removeDir(fs::FS& fs, const char* path) {
    std::cout << "[FileHandler:] Removing Dir: " << path << ", ";
    if (fs.rmdir(path)) {
      std::cout <<"Dir removed" << std::endl;
    } else {
      std::cout <<"rmdir failed" << std::endl;
    }
}

String FileHandler::readFile(fs::FS& fs, const char* path) {
    //std::cout << "[FileHandler:] Reading file: " << path;

    File file = fs.open(path);
    if (!file || file.isDirectory()) {
      throw("file does not exist");
    }
  
    //std::cout << "- read from file:" << std::endl;
    String data = file.readString();
    //Serial.println(data);
    file.close();
    return data;
}

void FileHandler::writeFile(fs::FS& fs, const char* path, const char* message) {
  std::cout << "[FileHandler] Writing file: "<<  path;

  File file = fs.open(path, FILE_WRITE, true);
  if (!file) {
    std::cout << "- failed to open file for writing" << std::endl;
    return;
  }
  if (file.print(message)) {
    std::cout << "- file written" << std::endl;
  } else {
    std::cout << "- write failed" << std::endl;
  }
  //Serial.println(message);
  file.close();
}