#include "String.h"

#define FILE_WRITE 1
class File {
    private:
    void* ptr;
    public:
    bool isDirectory();
    String readString();
    File openNextFile();
    char* name();
    char* path();
    int size();
    void close();
    bool print(const char* path);

};
namespace fs {
    class FS {
        private:
        public:
        bool mkdir(const char* path);
        bool rmdir(const char* path);
        File open(const char* path, int open = 0);
        int WriteFile(const char* path);
        
    };

}
