#ifndef ConfigH
#define ConfigH

#include <string>
#include <map>  
#include <vector>
#include <stdlib.h>
#include "Singleton.h"

#define CONFIG_FILENAME "/etc/mind.conf"

using namespace std;

class Config : public Singleton<Config> {
    public:
        bool reload(void);
        bool save(void);
        string getStringValue(string key, string defaultValue = "");
        bool   getBoolValue(string key, bool defaultValue = false);
        int    getIntValue(string key, int defaultValue = 0);
        vector<string> getListValue(string key, char separator = ';');
        map<string, string> getByPrefix(string prefix);

        void setValue(string key, string value);  
        
        friend class Singleton<Config>;      

		
    private:
		Config(string fileName = CONFIG_FILENAME);
        map<string, string> values;
		string fileName;
};

#define sConfig Config::instance()

#endif
