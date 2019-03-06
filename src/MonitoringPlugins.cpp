#include "MonitoringPlugins.h"

MonitoringPlugins::MonitoringPlugins(void)
{ 
    
    vector<string> names = sConfig->getListValue("MonitoringPlugins");
    vector<string>::iterator iter = names.begin();
    for (; iter != names.end(); ++iter) 
    {
        Library *plugin = NULL;
        InstanceFunction instance = NULL;
        InitFunction init = NULL;
        string filename = *iter + ".so";
        
        try
        {
            plugin = new Library(filename.c_str());
        }
        catch (char *error)
        {
            sLog->write(LOG_ERR, "Library error: %s.", error);
            delete plugin;
            continue;
        }
        
        if(plugin)
        {            
            init = (InitFunction) plugin->getSymbol("init");
            instance = (InstanceFunction) plugin->getSymbol("instance");
            
            if(init != NULL && instance != NULL )
            {
                if( true == init( sConfig->getByPrefix((*iter).c_str()) ) )
                {
                    addThread( instance(sQueue) );     
                } else
                {
                   sLog->write( LOG_ERR, "Error init plug %s\n", filename.c_str());
                   delete plugin;
                   continue; 
                }
            
            } else
            {
                sLog->write( LOG_ERR, "Error connecting plug %s\n", filename.c_str());
                delete plugin;
                continue;    
            }  
        } else
        {
            sLog->write( LOG_ERR, "Plugin %s is NULL\n", filename.c_str());
            continue;
        }
        plugins.push_back(plugin);
        sLog->write(LOG_NOTICE, "Plugin %s loaded", filename.c_str());           
    }
}

MonitoringPlugins::~MonitoringPlugins(void) {
    stop();
    vector<Library*>::iterator iter = plugins.begin();
    for (; iter != plugins.end(); ++iter)     
        delete *iter;    
    plugins.clear();    
}
