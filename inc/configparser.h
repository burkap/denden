#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

#define CONF_NON_EXIST "NON_EXIST"

class ConfigParser {
private:
    std::map<std::string, std::map<std::string, std::string>> map;
public:
    ConfigParser(std::string location){
        read(location);
    }

    std::string get_value(std::string section, std::string key, std::string default_value = CONF_NON_EXIST){
        if(map.find(section) == map.end()) return default_value;
        if(map[section].find(key) == map[section].end()) return default_value;
        return map[section][key];
    }

    void read(std::string location){
        std::ifstream file(location);
        if(file.is_open()){
            std::string line;
            std::string current_section = "-";
            while(getline(file, line)){
                line.erase(std::remove_if(line.begin(), line.end(), isspace),
                                     line.end());
                if(line[0] == '#' || line.empty())
                    continue;
                if(line[0] == '[') current_section = line.substr(1, line.size()-2);
                unsigned long pos = line.find("=");
                if(pos != std::string::npos && current_section != "-"){
                    std::string name = line.substr(0, pos);
                    std::string val = line.substr(pos + 1);
                    map[current_section].insert({name, val});
                }
            }
        }
        else{
            std::cout << "Couldn't open file: " << location << "\n";
        }
    }
};

#endif // CONFIGPARSER_H
