#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QString>
#include <QObject>
#include <QPointF>

class PluginInterface;
class PluginSystemInterface;
class CardGameEngineInterface;

class PluginInterface
{
public:
    virtual ~PluginInterface() {}
    virtual const QString &Name() = 0;
    virtual const QObject *Instance() = 0;
    virtual bool Initialize(PluginSystemInterface *pluginSystem) = 0;
};

struct Event {
    QString Name;
    QList<void *>Parameters;
};

class EventHandlerInterface
{
public:
    virtual ~EventHandlerInterface() {}
    virtual const QObject *Instance() = 0;
    virtual void ProcessEvent(Event &event) = 0;
};

class PluginSystemInterface
{
public:
    virtual ~PluginSystemInterface() {}
    virtual CardGameEngineInterface *GetEngine() = 0;
    virtual void AppendLog(const QString &line) = 0;
    virtual void RegisterEventHandler(const QString &event, EventHandlerInterface *handler) = 0;
};

class AbstractCard
{
public:
    virtual ~AbstractCard() {}
    virtual int GetHeight() = 0;
    virtual int GetWidth() = 0;

    virtual QString GetName() = 0;
};

class AbstractPlayer
{
public:
    virtual ~AbstractPlayer() {}
    virtual int GetHealth() = 0;
    virtual void SetHealth(int h) = 0;

    virtual int GetMaxHealth() = 0;
    virtual void SetMaxHealth(int h) = 0;

    virtual void AppendCard(AbstractCard* card) = 0;
    virtual AbstractCard * TakeCard(AbstractCard* card) = 0;
    virtual AbstractCard * TakeLastCard() = 0;

    virtual int GetID() = 0;
    virtual QString GetName() = 0;
    virtual QList<AbstractCard*> *GetCards() = 0;
    virtual bool IsYou() = 0;
    virtual QPointF GetCardsPosition() = 0;
    virtual void SetCardsPosition(QPointF newPos) = 0;
};

class CardGameEngineInterface
{
public:
    virtual ~CardGameEngineInterface() {}
    virtual AbstractPlayer* CreatePlayer(const QString &name, const int id) = 0;
    virtual void GiveCard(AbstractPlayer *player, AbstractCard* card) = 0;
    virtual void SelectCardAt(QPointF &pos) = 0;
};



Q_DECLARE_INTERFACE(PluginInterface, "org.test.PluginInterface/0.1");
Q_DECLARE_INTERFACE(PluginSystemInterface, "org.test.PluginSystemInterface/0.1");
Q_DECLARE_INTERFACE(EventHandlerInterface, "org.test.EventHandlerInterface/0.1");
Q_DECLARE_INTERFACE(CardGameEngineInterface, "org.test.CardGameEngineInterface/0.1");
Q_DECLARE_INTERFACE(AbstractCard, "org.test.AbstractCard/0.1");
Q_DECLARE_INTERFACE(AbstractPlayer, "org.test.AbstractPlayer/0.1");

#endif // PLUGININTERFACE_H
