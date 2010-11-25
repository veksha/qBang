#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QSettings>
#include <QStack>
#include <QTimer>

#include "ui/renderer.h"
#include "include/plugininterface.h"

const qreal MaxCardHeight = 100;

class CardGameEngine: public QObject, public CardGameEngineInterface
{
    Q_OBJECT
    Q_INTERFACES(CardGameEngineInterface)
public:
    CardGameEngine();
    AbstractPlayer* CreatePlayer(const QString &name, const int id);
    void GiveCard(AbstractPlayer *player, AbstractCard* card);
    void SelectCardAt(QPointF &pos);
    Renderer *renderer;

    QList<AbstractPlayer*> players;
    QHash<QString, AbstractCard*> cards;
    QStack<AbstractCard*> talon;

public slots:
    void dealTheCards();
    void takeAllCards();
    void shuffleTheTalon();

private:
    void loadCards();
};

#endif // LOGIC_H
