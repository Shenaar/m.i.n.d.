#include "Config.h"  
#include <fstream>
#include "Log.h"

Config::Config(string fileName) {
    this->fileName = fileName;
    reload();
}

bool Config::reload(void) {
    ifstream in(fileName.c_str());
    if (!in.is_open()) {
      sLog->write(LOG_ERR, "Config error: can't open file for reload!");
		return false;
	}
    values.clear();	
    while (!in.eof()) {
        string line;
        getline(in, line);
        if (line.length() == 0 || line[0] == '#') {
            continue;
        }
        int pos = line.find("=");
        // = can't be first or last
        if (pos <= 0 || pos == line.length() - 1) {
            sLog->write(LOG_WARNING, "Config warning: bad line \"%s\"", line.c_str());
            continue;
        }
        string key = line.substr(0, pos);
        string val = line.substr(pos + 1, line.length() - pos);
        values[key] = val;
    }
    in.close();
    return true;
}

bool Config::save(void) {    
    ofstream out(fileName.c_str());
    if (!out.is_open()) {
        sLog->write(LOG_ERR, "Config error: can't open file for save!");
        return false;
    }
    map<string, string>::iterator iter = values.begin();
    for (; iter != values.end(); ++iter) {
        out << iter->first << "=" << iter->second << endl;
    }
    out.close();
    return true;
}

string Config::getStringValue(string key, string defaultValue) {
    map<string, string>::iterator iter = values.find(key);
    if (iter == values.end()) {
        return defaultValue;
    }
    return iter->second;
}

bool Config::getBoolValue(string key, bool defaultValue) {
    string val = getStringValue(key);
    if (val == "") {
        return defaultValue;
    }
    return val == "yes" || val == "1" || val == "true";
}

int Config::getIntValue(string key, int defaultValue) {
    string val = getStringValue(key);
    if (val == "") {
        return defaultValue;
    }
    return atoi(val.c_str());
}

void Config::setValue(string key, string value) {
    values[key] = value;
}

map<string, string> Config::getByPrefix(string prefix) {
    map<string, string> result;
    map<string, string>::iterator iter = values.begin();
    string pref = prefix + ".";
    for (; iter != values.end(); ++iter) {
        string key = iter->first;
        string val = iter->second;
        if (key.find(pref) == 0) {
            result[key] = val;
        }
    } 
    return result;
}

vector<string> Config::getListValue(string key, char separator) {
    vector<string> result;
    string val = getStringValue(key);
    string sub;
    for (int i = 0; i < val.length(); ++i) {
        if (val[i] == separator) {
            result.push_back(sub);
            sub = "";
            continue;
        }
        sub += val[i];
    }
    if (sub != "") {
        result.push_back(sub);
    }
    return result;
}
