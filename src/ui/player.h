#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QFont>
#include "card.h"
#include <include/plugininterface.h>

class Player : public QGraphicsTextItem, public AbstractPlayer
{
    Q_OBJECT
    Q_INTERFACES(AbstractPlayer)
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
        maxHealth = health = 4;
    }
    int GetHealth() {
        return health;
    }
    int GetMaxHealth() {
        return maxHealth;
    }
    void SetHealth(int h) {
        health = h;
        if (health > maxHealth) maxHealth = health;
        refreshText();
    }
    void SetMaxHealth(int h) {
        maxHealth = h;
        if (health > maxHealth) health = maxHealth;
        refreshText();
    }
    void AppendCard(AbstractCard* card);
    AbstractCard * TakeCard(AbstractCard* card);
    AbstractCard * TakeLastCard();
    int GetID() {
        return id;
    }
    QString GetName() {
        return name;
    }
    QList<AbstractCard*> *GetCards() {
        return &cards;
    }
    bool IsYou() {
        return isYou;
    }
    QPointF GetCardsPosition() {
        return cardsPos;
    }
    void SetCardsPosition(QPointF newPos) {
        cardsPos = newPos;
    }
    void refreshText();
private:
    int health;
    int maxHealth;
    int id;
    QString name;
    QList<AbstractCard*> cards;
    bool isYou;
    QPointF cardsPos;
    //int role;
    //int character;
};

#endif // PLAYER_H
