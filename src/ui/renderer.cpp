#include "renderer.h"

Renderer::Renderer()
{
    scene.setSceneRect(0,0,1024,768);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setScene(&scene);
    setCacheMode(QGraphicsView::CacheBackground);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    scene.addRect(0,0,scene.width(), scene.height());
}

void Renderer::addPlayer(Player *player, QPointF position)
{
    player->setPos(position);
    scene.addItem(player);
}

void Renderer::addCard(Card *card, QPointF position)
{
    card->setPos(position);
    scene.addItem(card);
    QPropertyAnimation *anim = new QPropertyAnimation(card, "pos");
    anim->setDuration(500);
    anim->setEasingCurve(QEasingCurve::InOutSine);

    animations[card] = anim;
}

void Renderer::moveCard(Card *card, QPointF to)
{
    animations[card]->stop();
    animations[card]->setStartValue(card->pos());
    animations[card]->setEndValue(to);
    animations[card]->start();
}

void Renderer::moveCard(Card *card, QPointF from, QPointF to)
{
    animations[card]->stop();
    animations[card]->setStartValue(from);
    animations[card]->setEndValue(to);
    animations[card]->start();
}

void Renderer::beautifulMove(QList<Card *> &cards, QList<QPointF> &to)
{
    QParallelAnimationGroup *parallel = new QParallelAnimationGroup();

    int c = 0;
    for(int i = 0; i < cards.count(); i++)
    {
        Card* card = cards.at(i);
        if ( card->pos() != to.at(i) )
        {
            QSequentialAnimationGroup *seq = new QSequentialAnimationGroup(parallel);
            seq->addPause( (c++) * 100 );
            animations[card]->stop();
            animations[card]->setStartValue(card->pos());
            animations[card]->setEndValue(to.at(i));
            seq->addAnimation(animations[card]);
        }
    }
    parallel->start();
}

void Renderer::beautifulMove(QList<Card *> &cards, QPointF &to)
{
    QList<QPointF> tmp;

    for(int i=0; i < cards.count(); i++)
        tmp.append(to);

    beautifulMove(cards, tmp);
}

void Renderer::beautifulMove(QStack<Card *> &cards, QPointF &to)
{
    QList<Card *> tmpCards;
    QList<QPointF> tmpTo;

    foreach(Card *card, cards)
    {
        tmpCards.append(card);
        tmpTo.append(to);
    }

    beautifulMove(tmpCards, tmpTo);
}

void Renderer::arrangeCards(QList<Card *>cards, QPointF topCenter)
{
    const qreal spacing = -25;
    qreal totalWidth = 0;
    QList<QPointF> positions;

    foreach(Card *card, cards)
        totalWidth += card->width();
    totalWidth += spacing * (cards.count() - 1);

    // leftmost start point
    int x = topCenter.x() - totalWidth / 2;

    for(int i = 0; i < cards.count(); i++)
    {
        Card *card = cards.at(i);

        card->setZValue(-i);
        positions.append(QPointF(x, topCenter.y()));

        x += card->width() + spacing;
    }
    beautifulMove(cards, positions);
}

