#include "cardgameengine.h"

CardGameEngine::CardGameEngine(): QObject()
{
    renderer = new Renderer();
    
    connect(renderer, SIGNAL(onClick(QMouseEvent*)), SLOT(onClick(QMouseEvent*)));
    connect(renderer, SIGNAL(onMouseMove(QMouseEvent*)), SLOT(onMouseMove(QMouseEvent*)));
    connect(renderer, SIGNAL(onDoubleClick(QMouseEvent*)),
            SLOT(onDoubleClick(QMouseEvent*)));
    
    loadCards();
    
    pluginSystem.SetEngine(this);
    pluginSystem.LoadPlugins("../qBang/QtPlugin-build/debug/");
}

AbstractPlayer* CardGameEngine::CreatePlayer(const QString &name, const int id)
{
    Player *player = new Player(name, id, id == 1);
    players.append(player);

    switch (id)
    {
    case 1:
        renderer->addPlayer( player, QPointF(renderer->scene.width()/2,
                                             0) );
        player->SetCardsPosition( QPointF( player->pos().x(),
                                    player->pos().y() + player->font().pointSizeF() + 20 ) );
        break;
    case 2:
        renderer->addPlayer( player, QPointF(renderer->scene.width()/2,
                                             renderer->scene.height()-50) );
        player->SetCardsPosition( QPointF( player->pos().x(),
                                    player->pos().y() - MaxCardHeight ) );
        break;
    }

    return player;
}

void CardGameEngine::loadCards()
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
    foreach( AbstractCard *card, cards.values() )
    {
        renderer->addCard( card, QPointF() );
        talon.push( card );
    }
}

void CardGameEngine::takeAllCards()
{
    // arrange talon if it's scattered
    renderer->beautifulMove(&talon, QPointF());
    foreach(AbstractCard* card, talon)
        card->SetSelected(false);

    // take all cards from players
    foreach ( AbstractPlayer *player, players )
    {
        renderer->beautifulMove( player->GetCards(), QPointF() );
        while ( !player->GetCards()->isEmpty() )
        {
            AbstractCard * card = player->TakeLastCard();
            card->SetSelected(false);
            talon.push( card );
        }
        ((Player*)player)->refreshText();
    }
}

void CardGameEngine::dealTheCards()
{
    // no comments :)
    takeAllCards();
    shuffleTheTalon();

    // deal the cards to players
    foreach ( AbstractPlayer *player, players )
    {
        while ( !talon.isEmpty() && ( player->GetCards()->count() < player->GetMaxHealth()) )
            GiveCard( player, talon.pop() );
        ((Player*)player)->refreshText();
    }
}

void CardGameEngine::shuffleTheTalon()
{
    if (talon.count() == 0) return;
    
    QStack<AbstractCard*> tmp;

    foreach(AbstractCard* card, talon)
        tmp.insert( qrand() % (tmp.size()+1), card );

    talon = tmp;
}

void CardGameEngine::GiveCard(AbstractPlayer *player, AbstractCard* card)
{
    player->AppendCard( card );
    renderer->arrangeCards( player->GetCards(), player->GetCardsPosition() );
}

void CardGameEngine::SelectDeselectCardAt(QPointF &pos)
{
    QList<QGraphicsItem *> items = renderer->scene.items(pos);

    foreach (QGraphicsItem *item, items)
    {
        Card *card = qgraphicsitem_cast<Card *>(item);
        if (card)
        {
            qDebug() << card->GetName();

            qreal yShift = card->GetSelected() ? -10 : 10 ;
            QPointF newPos = QPointF( card->GetOncomingPosition().x(),
                                      card->GetOncomingPosition().y() - yShift );
            card->SetSelected(!card->GetSelected());
            renderer->moveCard(card, newPos);
            break;
        }
        else
        {
            qDebug() << "no card";
            // TODO: implement deselecting animation
        }
    }
}

void CardGameEngine::onClick(QMouseEvent* e)
{
    Event ev;
    ev.Name = "Core/Click";
    ev.Parameters.append( &renderer->mapToScene(e->pos()) );
    pluginSystem.SendEvent(ev);
}

void CardGameEngine::onMouseMove(QMouseEvent* e)
{
    Event ev;
    ev.Name = "Core/MouseMove";
    ev.Parameters.append( &renderer->mapToScene(e->pos()) );
    pluginSystem.SendEvent(ev);
}

void CardGameEngine::onDoubleClick(QMouseEvent* e)
{
    Event ev;
    ev.Name = "Core/DoubleClick";
    ev.Parameters.append( &renderer->mapToScene(e->pos()) );
    pluginSystem.SendEvent(ev);
}

void CardGameEngine::onGameStart()
{
    Event ev;
    ev.Name = "Core/GameStart";
    pluginSystem.SendEvent(ev);
}


