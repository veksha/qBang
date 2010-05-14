#include "logic.h"

Logic::Logic(): QObject()
{
    renderer = new Renderer();
    loadCards();
}

Player* Logic::createPlayer(const QString &name, const int id)
{
    Player *player = new Player(name, id, id == 1);
    players.append(player);

    switch (id)
    {
    case 1:
        renderer->addPlayer(player, QPointF(renderer->scene.width()/2, 0));
        break;
    case 2:
        renderer->addPlayer(player, QPointF(renderer->scene.width()/2, renderer->scene.height()-50));
        break;
    }

    return player;
}

void Logic::loadCards()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "qBang", "settings");
    settings.beginGroup("cards");

//    for (int i = 1; i <= 15; i++)
//        settings.setValue("bang" + QString::number(i), "c:\\bang.png");
//    for (int i = 1; i <= 15; i++)
//        settings.setValue("miss" + QString::number(i), "c:\\miss.png");

    QStringList keys = settings.childKeys();
    for (int i = 0; i < keys.count(); i++)
        cards[keys.at(i)] = new Card( keys.at(i),
            QPixmap(settings.value(keys.at(i), "c:\\bang.png").toString()) );

    settings.endGroup();

    foreach( Card *card, cards.values() )
    {
        renderer->addCard( card, QPointF() );
        talon.push( card );
    }
}

void Logic::takeAllCards()
{
    // take cards from all players
    foreach ( Player *player, players )
    {
        while ( !player->cards.isEmpty() )
        {
            Card * card = player->takeLastCard();
            talon.push( card );
            renderer->moveCard( card, QPointF() );
        }
        player->refreshText();
    }
}

void Logic::dealTheCards()
{
    takeAllCards();
    shuffleTheTalon();

    // deal the cards to players
    foreach ( Player *player, players )
    {
        while ( !talon.isEmpty() && ( player->cards.count() < player->maxHealth) )
        {
            renderer->moveCard( talon.top(),
                QPointF(300 + player->cards.count() * 80 + qrand() % 20,
                        player->id * 200 + qrand() % 20) );
            player->giveCard( talon.pop() );
        }
        player->refreshText();
    }
}

void Logic::shuffleTheTalon()
{
    QStack<Card*> tmp;
    QStack<Card*>::iterator i = talon.begin();

    do
    {
        tmp.insert( qrand() % (tmp.size()+1), *i );
        i++;
    }
    while ( i != talon.end() );
    talon = tmp;
}
