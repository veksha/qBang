#ifndef PLUGINSYSTEM_H
#define PLUGINSYSTEM_H

#include <QObject>
#include <QLibrary>
#include <QPluginLoader>
#include <QFile>
#include <QDebug>
#include <QDir>

#include <include/plugininterface.h>

class PluginSystem : public QObject, public PluginSystemInterface
{
    Q_OBJECT
public:
    QList<PluginInterface *> Plugins;
    QHash<QString, QList<EventHandlerInterface *> > EventHandlersInfo;
    explicit PluginSystem(QObject *parent = 0);
    PluginInterface *LoadPlugin(const QString &fileName);
    void LoadPlugins(const QString &dirPath);
    void UnloadPlugin(PluginInterface *plugin);
    void UnloadAllPlugins();
    void RegisterEventHandler(const QString &event, EventHandlerInterface *handler);
    void SendEvent(Event &event);
    void Log(const QString &line);
private:
    QPluginLoader loader;
signals:
    void AppendLog(const QString &line);
};

#endif // PLUGINSYSTEM_H
