#include <fstream>
#include <string>
#include "readcfg.hpp"

bool readcfg(std::map<std::string, std::string> &cfg_map)
{
    std::ifstream cfg_stream("config.cfg");
    if(!cfg_stream.is_open())
    {
       std::cout << "error: couldn't open config.cfg\n";
       return 0;
    }

    std::string buffer;
    while (cfg_stream >> buffer)
    {
        if (cfg_map.find(buffer) != cfg_map.end())
        {
            std::string x;
            cfg_stream >> x;
            cfg_map[buffer] = x;
        }
        else
        {
            std::cout << buffer << "\n error: couldn't read config.cfg correctly\n";
            return 0;
        }
    }
    return 1;
}