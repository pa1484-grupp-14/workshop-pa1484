#pragma 
#include <string>
#include <memory>

using namespace std;
class StationObject
{
private:
    string key;
    string name;
    int longitude;
    int latitude;
public:
    StationObject(string key, string name, int longitude, int latitude);
    string getKey();
    string getName();
    int getLon();
    int getLat();

    void setKey(string key);
    void setName(string name);
    void setLon(int lon);
    void setLat(int lat);
};
