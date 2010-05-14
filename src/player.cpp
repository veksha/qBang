#include "player.h"

void Player::refreshText()
{
    setHtml(QString("%1 (%2 cards, %3 hp)%4").arg(name).arg(cards.count()).arg(health).arg(isYou?" You":""));
}

void Player::giveCard(Card * card)
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
