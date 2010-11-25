#include "pluginsystem.h"

PluginSystem::PluginSystem(QObject *parent) :
        QObject(parent)
{
}

PluginInterface *PluginSystem::LoadPlugin(const QString &fileName)
{
    PluginInterface *plugin;

    if ( !QFile::exists(fileName) )
    {
        Log(QString("file not found (%1)").arg(fileName));
        return 0;
    }
    else
    {
        Log(QString("loading plugin (%1)").arg(fileName));
        loader.setFileName(fileName);
        plugin = qobject_cast<PluginInterface*>(loader.instance());
        
        if (Plugins.contains(plugin))
        {
            Log(QString("plugin was already loaded!").arg(plugin->Name()));
            return 0;
        }

        if (plugin->Initialize(this))
        {
            Plugins.append(plugin);
            Log(QString("plugin \"%1\" loaded successfully").arg(plugin->Name()));
        }
    }

    return plugin;
}

void PluginSystem::LoadPlugins(const QString &dirPath)
{
    QDir dir(dirPath);
    foreach (QString entry, dir.entryList())
    {
        if (QLibrary::isLibrary(entry))
            LoadPlugin(QDir::toNativeSeparators(dir.absolutePath()) \
                       + QDir::separator() \
                       + entry);
    }
}

void PluginSystem::UnloadPlugin(PluginInterface *plugin)
{
    Plugins.removeOne(plugin);
    delete plugin;
    plugin = NULL;
}

void PluginSystem::UnloadAllPlugins()
{
    foreach (PluginInterface *plugin, Plugins)
    {
        delete plugin;
        plugin = NULL;
    }
}

void PluginSystem::RegisterEventHandler(const QString &event, EventHandlerInterface *handler)
{
    PluginInterface *plugin = qobject_cast<PluginInterface *>(handler->Instance());
    Log(QString("\"%1\" is registering event \"%2\"").arg(plugin->Name(), event));
    
    EventHandlersInfo[event].append(handler);
}

void PluginSystem::Log(const QString &line)
{
    AppendLog(QString("PluginSystem:\t%1").arg(line));
}

void PluginSystem::SendEvent(Event &event)
{
    QList<EventHandlerInterface *> handlers;
    handlers = EventHandlersInfo[event.Name];
    
    foreach(EventHandlerInterface *handler, handlers)
        handler->ProcessEvent(event);
}


