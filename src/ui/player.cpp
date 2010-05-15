#include "player.h"

void Player::refreshText()
{
    setHtml( QString("%1 (%2 cards, %3/%4 hp)%5")
             .arg(name)
             .arg(cards.count())
             .arg(health)
             .arg(maxHealth)
             .arg(isYou ? " You" : "") );
}

void Player::appendCard(Card * card)
{
    cards.append(card);
}

Card * Player::takeCard(Card * card)
{
    cards.removeOne(card);
    return card;
}

Card * Player::takeLastCard()
{
    return cards.takeLast();
}
