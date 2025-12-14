#include "FileHandling.h"
#include <iostream>

#define FORMAT_LITTLEFS_IF_FAILED true 

// List all of the files inside a given folder
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

// Create a new folder on the Device
void FileHandler::createDir(fs::FS& fs, const char* path) {
    std::cout << "[FileHandler] Creating Dir: " << path << ", ";
    if (fs.mkdir(path)) {
      std::cout << "Dir created" << std::endl;
    } else {
      std::cout << "mkdir failed" << std::endl;
    }
}

//Remove a given folder
void FileHandler::removeDir(fs::FS& fs, const char* path) {
    std::cout << "[FileHandler:] Removing Dir: " << path << ", ";
    if (fs.rmdir(path)) {
      std::cout <<"Dir removed" << std::endl;
    } else {
      std::cout <<"rmdir failed" << std::endl;
    }
}

// Read a given file to string
String FileHandler::readFile(fs::FS& fs, const char* path) {

    File file = fs.open(path);
    if (!file || file.isDirectory()) {
      throw("file does not exist");
    }
  
    String data = file.readString();
    file.close();
    return data;
}

// Write a given string to a file and close it
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
  file.close();
}