#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QSettings>
#include <QStack>
#include <QTimer>

#include "ui/renderer.h"
#include "include/plugininterface.h"
#include "pluginsystem.h"

const qreal MaxCardHeight = 100;

class CardGameEngine: public QObject, public CardGameEngineInterface
{
    Q_OBJECT
    Q_INTERFACES(CardGameEngineInterface)
public:
    PluginSystem pluginSystem;
    Renderer *renderer;
    QList<AbstractPlayer*> players;
    QHash<QString, AbstractCard*> cards;
    QStack<AbstractCard*> talon;

    CardGameEngine();
    AbstractPlayer* CreatePlayer(const QString &name, const int id);
    void GiveCard(AbstractPlayer *player, AbstractCard* card);
    void SelectDeselectCardAt(QPointF &pos);

public slots:
    void dealTheCards();
    void takeAllCards();
    void shuffleTheTalon();
    void onGameStart();
    void onClick(QMouseEvent*);
    void onMouseMove(QMouseEvent*);
    void onDoubleClick(QMouseEvent*);

private:
    void loadCards();
};

#endif // LOGIC_H
