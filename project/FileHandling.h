#ifdef LILYGO_BUILD
#include <LittleFS.h>
#endif
#ifdef NATIVE_BUILD
#include "nativeReplacements/LittleFS.h"
#endif

struct FileHandler
{
public:
    void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
    void createDir(fs::FS &fs, const char *path);
    void removeDir(fs::FS &fs, const char *path); 
    String readFile(fs::FS &fs, const char *path);
    void writeFile(fs::FS &fs, const char *path, const char *message);
    //void appendFile(fs::FS &fs, const char *path, const char *message);
    //void renameFile(fs::FS &fs, const char *path1, const char *path2);
    //void deleteFile(fs::FS &fs, const char *path);
};