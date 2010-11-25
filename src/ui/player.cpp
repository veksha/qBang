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

void Player::AppendCard(AbstractCard *card)
{
    cards.append(card);
}

AbstractCard * Player::TakeCard(AbstractCard * card)
{
    cards.removeOne(card);
    return card;
}

AbstractCard* Player::TakeLastCard()
{
    return cards.takeLast();
}
