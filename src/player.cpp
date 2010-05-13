#include "player.h"

void Player::refreshText()
{
    setHtml(QString("%1 (%2 cards, %3 hp)%4").arg(name).arg(cards.count()).arg(health).arg(isYou?" You":""));
}

void Player::GiveCard(Card * card)
{
    cards.append(card);
}

Card * Player::TakeCard(Card * card)
{
    cards.removeOne(card);
    return card;
}

Card * Player::TakeFirstCard()
{
    return cards.takeFirst();
}
