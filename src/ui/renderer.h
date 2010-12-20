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
#include <include/plugininterface.h>

class Renderer : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene scene;
    QHash<AbstractCard*, QPropertyAnimation*> animations;

    Renderer();
    void createCardAnimation(AbstractCard *card);
    void addCard(AbstractCard *card, QPointF position);
    void addPlayer(AbstractPlayer *player, QPointF position);
    void moveCard(AbstractCard *card, QPointF to);
    void moveCard(AbstractCard *card, QPointF from, QPointF to);
    void beautifulMove(QList<AbstractCard *> *cards, QPointF to);
    void beautifulMove(QStack<AbstractCard *> *cards, QPointF to);
    void beautifulMove(QList<AbstractCard *> *cards, QList<QPointF> to);
    void arrangeCards(QList<AbstractCard *> *cards, QPointF center);
private:
    void mousePressEvent(QMouseEvent *event) { emit onClick(event); }
    void mouseMoveEvent(QMouseEvent *event) { emit onMouseMove(event); }
    void mouseDoubleClickEvent(QMouseEvent *event) { emit onDoubleClick(event); }
signals:
    void onClick(QMouseEvent *event);
    void onMouseMove(QMouseEvent *event);
    void onDoubleClick(QMouseEvent *event);
protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};

#endif // RENDERER_H
