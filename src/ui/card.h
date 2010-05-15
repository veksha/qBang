#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>

class Card: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
            Card(const QString &name, QPixmap pix): QObject(), QGraphicsPixmapItem(pix)
    {
        setCacheMode(DeviceCoordinateCache);
        this->name = name;
    }
    int height() const { return pixmap().height(); }
    int width() const { return pixmap().width(); }

    QString name;
};

#endif // CARD_H
