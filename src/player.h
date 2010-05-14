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
        QFont font;
        font.setPointSize(16);
        setFont(font);

        this->name = name;
        this->id = id;
        this->isYou = isYou;
        maxHealth = 4;
        setHealth(maxHealth);
    }

    int health;
    void setHealth(int h) {
        health = h;
        if (health > maxHealth) maxHealth = health;
        refreshText();
    }

    int maxHealth;
    void setMaxHealth(int h) {
        maxHealth = h;
        if (health > maxHealth) health = maxHealth;
        refreshText();
    }

    void refreshText();
    void giveCard(Card* card);
    Card * takeCard(Card* card);
    Card * takeLastCard();

    int id;
    QString name;
    QList<Card*> cards;
    //int role;
    //int character;
    bool isYou;
private:

};

#endif // PLAYER_H
