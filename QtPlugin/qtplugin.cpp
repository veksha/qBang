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
    
    m_pluginSystem->RegisterEventHandler("Core/GameStart", this);
    m_pluginSystem->RegisterEventHandler("Core/Click", this);
    //m_pluginSystem->RegisterEventHandler("Core/MouseMove", this);
    m_pluginSystem->RegisterEventHandler("Core/DoubleClick", this);
    
    return true;
}

void QtPlugin::ProcessEvent(Event &event)
{
    //Log(QString("Processing \"%1\" event...").arg(event.Name));
    if (event.Name == "Core/GameStart")
    {
        if (event.Parameters.count() >= 1 )
        {
            QString p0 = *((QString *)event.Parameters.at(0));
            Log(QString("The game is started! %1").arg(p0));
            OnGameStart();
        } else
        {
            Log(QString("The game is started!"));
            OnGameStart();
        }
    }
    else if (event.Name == "Core/Click")
    {
        if (event.Parameters.count() >= 1 )
        {
            QPointF p0 = *((QPointF *)event.Parameters.at(0));
            Log( QString("plugin have gotten click event! %1,%2")
                 .arg(p0.x()).arg(p0.y()) );
            OnClick(p0);
        }
    }
    else if (event.Name == "Core/DoubleClick")
    {
        if (event.Parameters.count() >= 1 )
        {
            QPointF p0 = *((QPointF *)event.Parameters.at(0));
            Log( QString("plugin have gotten doubleclick event! %1,%2")
                 .arg(p0.x()).arg(p0.y()) );
            OnDoubleClick(p0);
        }
    }
}

void QtPlugin::Log(const QString& line)
{
    m_pluginSystem->AppendLog(QString("QtPlugin:\t%1").arg(line));
}

void QtPlugin::OnGameStart()
{
    
}

void QtPlugin::OnClick(QPointF &pos)
{
    Q_UNUSED(pos)
}

void QtPlugin::OnMouseMove(QPointF &pos)
{
    Q_UNUSED(pos)
}

void QtPlugin::OnDoubleClick(QPointF &pos)
{
    Q_UNUSED(pos)
}





Q_EXPORT_PLUGIN2(QtPlugin,QtPlugin);
