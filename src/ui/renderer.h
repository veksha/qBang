#ifndef RENDERER_H
#define RENDERER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>

#include "card.h"
#include "player.h"

class Renderer : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene scene;
    QHash<Card*, QPropertyAnimation*> animations;

    Renderer();
    void addCard(Card *card, QPointF position);
    void addPlayer(Player *player, QPointF position);
    void moveCard(Card *card, QPointF to);
    void moveCard(Card *card, QPointF from, QPointF to);
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
