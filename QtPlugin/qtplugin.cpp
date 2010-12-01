#include "qtplugin.h"

QtPlugin::QtPlugin()
{
    m_Name = "Bang! game";
}

QtPlugin::~QtPlugin()
{
    Log("destroying plugin!");
}

const QString &QtPlugin::Name()
{
    return m_Name;
}

const QObject *QtPlugin::Instance()
{
    return this;
}

bool QtPlugin::Initialize(PluginSystemInterface *pluginSystem)
{
    m_pluginSystem = pluginSystem;
    m_engine = m_pluginSystem->GetEngine();
    
    m_engine->CreatePlayer("yura", 1)->SetHealth(5);
    m_engine->CreatePlayer("vova", 2)->SetHealth(4);
    
    m_pluginSystem->RegisterEventHandler("Core/GameStarted", this);
    return true;
}

void QtPlugin::ProcessEvent(Event &event)
{
    Log(QString("Processing \"%1\" event...").arg(event.Name));
    if (event.Name == "Core/GameStarted")
    {
        if (event.Parameters.count() >= 1 )
        {
            QString *p0 = ((QString *)event.Parameters.at(0));
            Log(QString("The game is started! %1").arg(*p0));
        }
    }
}

void QtPlugin::Log(const QString& line)
{
    m_pluginSystem->AppendLog(QString("QtPlugin:\t%1").arg(line));
}

Q_EXPORT_PLUGIN2(QtPlugin,QtPlugin);
