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

void Renderer::addPlayer(AbstractPlayer *player, QPointF position)
{
    ((Player*)player)->setPos(position);
    scene.addItem((Player*)player);
}

void Renderer::createCardAnimation(AbstractCard *card)
{
    QPropertyAnimation *anim = new QPropertyAnimation((Card*)card, "pos");
    anim->setDuration(500);
    anim->setEasingCurve(QEasingCurve::InOutSine);

    animations[card] = anim;
}

void Renderer::addCard(AbstractCard *card, QPointF position)
{
    ((Card*)card)->setPos(position);
    scene.addItem((Card*)card);
    createCardAnimation(card);
}

void Renderer::moveCard(AbstractCard *card, QPointF to)
{
    animations[card]->stop();
    animations[card]->setStartValue(((Card*)card)->pos());
    animations[card]->setEndValue(to);
    card->SetOncomingPosition(to);
    animations[card]->start();
}

void Renderer::moveCard(AbstractCard *card, QPointF from, QPointF to)
{
    animations[card]->stop();
    animations[card]->setStartValue(from);
    animations[card]->setEndValue(to);
    card->SetOncomingPosition(to);
    animations[card]->start();
}

void Renderer::beautifulMove(QList<AbstractCard *> *cards, QList<QPointF> to)
{
    int c = 0;
    for(int i = 0; i < cards->count(); i++)
    {
        AbstractCard* card = cards->at(i);
        if ( animations[card]->group() )
        {
            animations[card]->group()->stop();
            animations[card]->group()->removeAnimation(animations[card]);
            delete animations[card]->group();
        }

        if ( ((Card*)card)->pos() != to.at(i) )
        {
            QSequentialAnimationGroup *seq = new QSequentialAnimationGroup();
            seq->addPause( (c++) * 100 );
            animations[card]->setStartValue( ((Card*)card)->pos() );
            animations[card]->setEndValue(to.at(i));
            seq->addAnimation(animations[card]);
            card->SetOncomingPosition(to.at(i));
            seq->start();
        }
    }
}

void Renderer::beautifulMove(QList<AbstractCard *> *cards, QPointF to)
{
    QList<QPointF> tmp;

    for(int i=0; i < cards->count(); i++)
        tmp.append(to);

    beautifulMove(cards, tmp);
}

void Renderer::beautifulMove(QStack<AbstractCard *> *cards, QPointF to)
{
    QList<AbstractCard *> tmpCards;
    QList<QPointF> tmpTo;

    foreach(AbstractCard *card, *cards)
    {
        tmpCards.append(card);
        tmpTo.append(to);
    }

    beautifulMove(&tmpCards, tmpTo);
}

void Renderer::arrangeCards(QList<AbstractCard *> *cards, QPointF topCenter)
{
    const qreal spacing = -25;
    qreal totalWidth = 0;
    QList<QPointF> positions;

    foreach(AbstractCard *card, *cards)
        totalWidth += card->GetWidth();
    totalWidth += spacing * (cards->count() - 1);

    // leftmost start point
    int x = topCenter.x() - totalWidth / 2;

    for(int i = 0; i < cards->count(); i++)
    {
        AbstractCard *card = cards->at(i);

        ((Card*)card)->setZValue(-i);
        positions.append(QPointF(x, topCenter.y()));

        x += card->GetWidth() + spacing;
    }
    beautifulMove(cards, positions);
}

