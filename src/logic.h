#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QSettings>
#include <QStack>
#include <QTimer>

#include "ui/card.h"
#include "ui/renderer.h"
#include "ui/player.h"

const qreal MaxCardHeight = 100;

class Logic: public QObject
{
    Q_OBJECT
public:
    Logic();
    Player* createPlayer(const QString &name, const int id);
    void giveCard(Player *player, Card* card);
    Renderer *renderer;

    QList<Player*> players;
    QHash<QString,Card*> cards;
    QStack<Card*> talon;

public slots:
    void dealTheCards();
    void takeAllCardsFromPlayers();
    void shuffleTheTalon();

private:
    void loadCards();
};

#endif // LOGIC_H
