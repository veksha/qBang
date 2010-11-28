#ifndef QTPLUGIN_H
#define QTPLUGIN_H

#include <QtPlugin>
#include "../include/plugininterface.h"

class QtPlugin : public QObject, PluginInterface, EventHandlerInterface {
    Q_OBJECT
    Q_INTERFACES(PluginInterface EventHandlerInterface)
public:
    QtPlugin();
    ~QtPlugin();

    const QString &Name();
    const QObject *Instance();
    bool Initialize(PluginSystemInterface *pluginSystem);
    void ProcessEvent(Event &event);
    void Log(const QString& line);
    
protected:
    PluginSystemInterface *m_pluginSystem;
    QString m_Name;
};

#endif // QTPLUGIN_H
