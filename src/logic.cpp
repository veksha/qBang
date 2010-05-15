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
        renderer->addPlayer( player, QPointF(renderer->scene.width()/2,
                                             0) );
        player->cardsPos = QPointF( player->pos().x(),
                                    player->pos().y() + player->font().pointSizeF() + 20 );
        break;
    case 2:
        renderer->addPlayer( player, QPointF(renderer->scene.width()/2,
                                             renderer->scene.height()-50) );
        player->cardsPos = QPointF( player->pos().x(),
                                    player->pos().y() - MaxCardHeight );
        break;
    }

    return player;
}

void Logic::loadCards()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "qBang", "settings");
    settings.beginGroup("cards");

    // write settings
    for (int i = 1; i <= 15; i++)
        settings.setValue("bang" + QString::number(i), ":/res/bang.png");
    for (int i = 1; i <= 15; i++)
        settings.setValue("miss" + QString::number(i), ":/res/miss.png");

    // read settings
    QStringList keys = settings.childKeys();
    for (int i = 0; i < keys.count(); i++)
        cards[keys.at(i)] = new Card( keys.at(i),
                                      QPixmap(settings.value(keys.at(i), ":/res/bang.png").toString()) );

    settings.endGroup();

    // fill talon with cards
    foreach( Card *card, cards.values() )
    {
        renderer->addCard( card, QPointF() );
        talon.push( card );
    }
}

void Logic::takeAllCardsFromPlayers()
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
    // no comments :)
    takeAllCardsFromPlayers();
    shuffleTheTalon();

    // deal the cards to players
    foreach ( Player *player, players )
    {
        while ( !talon.isEmpty() && ( player->cards.count() < player->maxHealth) )
            giveCard( player, talon.pop() );
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

void Logic::giveCard(Player *player, Card* card)
{
    player->appendCard( card );
    renderer->arrangeCards( player->cards, player->cardsPos );
}

