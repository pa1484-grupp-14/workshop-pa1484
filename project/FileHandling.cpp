#include "FileHandling.h"
#include <iostream>
#ifdef LILYGO_BUILD
#include <Arduino.h>
#else
#include <String.h>
#endif
#define FORMAT_LITTLEFS_IF_FAILED true 

void FileHandler::listDir(fs::FS& fs, const char* dirname, uint8_t levels) {
  std::cout << "Listing directory: " << dirname << std::endl;

  File root = fs.open(dirname);
  if (!root) {
    std::cout << "- failed to open directory" << std::endl;
    return;
  }
  if (!root.isDirectory()) {
    std::cout << " - not a directory" << std::endl;
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      std::cout << "  DIR : " << std::endl;
      std::cout << file.name() << std::endl;
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      std::cout << "  FILE: " << std::endl;
      std::cout << file.name() << std::endl;
      std::cout << "\tSIZE: " << std::endl;
      std::cout << file.size() << std::endl;
    }
    file = root.openNextFile();
  }
}

void FileHandler::createDir(fs::FS& fs, const char* path) {
    std::cout << "reating Dir: " << path << std::endl;
    if (fs.mkdir(path)) {
      std::cout << "Dir created" << std::endl;
    } else {
      std::cout << "mkdir failed" << std::endl;
    }
}

void FileHandler::removeDir(fs::FS& fs, const char* path) {
    std::cout << "Removing Dir: " << path << std::endl;
    if (fs.rmdir(path)) {
      std::cout << "Dir removed" << std::endl;
    } else {
      std::cout << "rmdir failed" << std::endl;
    }
}

String FileHandler::readFile(fs::FS& fs, const char* path) {
    std::cout << "Reading file: " << path << std::endl;

    File file = fs.open(path);
    if (!file || file.isDirectory()) {
       throw("file does not exist");
    }
  
    std::cout << "- read from file:"  << std::endl;
    String data = file.readString();
    file.close();
    return data;
}

void FileHandler::writeFile(fs::FS& fs, const char* path, const char* message) {
  std::cout << "Writing file: "<< path << std::endl;

  File file = fs.open(path, FILE_WRITE);
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

void FileHandler::appendFile(fs::FS& fs, const char* path, const char* message) {
    std::cout << "Appending to file: %s\r\n" << path << std::endl;

    File file = fs.open(path, FILE_APPEND);
    if (!file) {
      std::cout << "- failed to open file for appending" << std::endl;
      return;
    }
    if (file.print(message)) {
      std::cout << "- message appended" << std::endl;
    } else {
      std::cout << "- append failed" << std::endl;
    }
    file.close();
}

void FileHandler::renameFile(fs::FS& fs, const char* path1, const char* path2) {
    std::cout << "Renaming file " << path1<<" to "<<path2 << std::endl;
    if (fs.rename(path1, path2)) {
      std::cout << "- file renamed" << std::endl;
    } else {
      std::cout << "- rename failed" << std::endl;
    }
}

void FileHandler::deleteFile(fs::FS& fs, const char* path) {
    std::cout << "Deleting file: " << path  << std::endl;
    if (fs.remove(path)) {
      std::cout << "- file deleted" << std::endl;
    } else {
      std::cout << "- delete failed" << std::endl;
    }
}
