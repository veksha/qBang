#ifndef RENDERER_H
#define RENDERER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>
#include <QStack>

#include "card.h"
#include "player.h"

class Renderer : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene scene;
    QHash<Card*, QPropertyAnimation*> animations;

    Renderer();
    void createCardAnimation(Card *card);
    void addCard(Card *card, QPointF position);
    void addPlayer(Player *player, QPointF position);
    void moveCard(Card *card, QPointF to);
    void moveCard(Card *card, QPointF from, QPointF to);
    void beautifulMove(QList<Card *> &cards, QPointF to);
    void beautifulMove(QStack<Card *> &cards, QPointF to);
    void beautifulMove(QList<Card *> &cards, QList<QPointF> to);
    void arrangeCards(QList<Card *>cards, QPointF center);
private:
    void mousePressEvent(QMouseEvent *event) { emit onClick(event); }
    void mouseMoveEvent(QMouseEvent *event) { emit onMouseMove(event); }
signals:
    void onClick(QMouseEvent *event);
    void onMouseMove(QMouseEvent *event);
protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};

#endif // RENDERER_H
