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
    animations[card]->setStartValue(from);
    animations[card]->setEndValue(to);
    animations[card]->start();
}

