#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QFont>
#include "card.h"

class Player : public QGraphicsTextItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Player(const QString &name, const int id, bool isYou = false)
        :QGraphicsTextItem(name)
    {
        this->name = name;
        this->id = id;
        this->isYou = isYou;
        maxHealth = 4;
        health =  maxHealth;

        QFont font;
        font.setPointSize(16);
        setFont(font);
        refreshText();
    }

    void refreshText();
    void GiveCard(Card* card);
    Card * TakeCard(Card* card);
    Card * TakeFirstCard();

    int id;
    QString name;
    QList<Card*> cards;
    //int role;
    //int character;
    int maxHealth;
    int health;
    bool isYou;
};

#endif // PLAYER_H
