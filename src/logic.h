#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QSettings>
#include <QStack>
#include <QTimer>

#include "card.h"
#include "renderer.h"
#include "player.h"

class Logic: public QObject
{
    Q_OBJECT
public:
    Logic();
    void createPlayer(const QString &name, const int id);
    Renderer *renderer;

    QList<Player*> players;
    QHash<QString,Card*> cards;
    QStack<Card*> talon;

public slots:
    void dealTheCards();
    void takeAllCards();

private:
    void loadCards();
};

#endif // LOGIC_H
