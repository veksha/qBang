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
        setObjectName(name);
    }
    int height() const { return pixmap().height(); }
    int width() const { return pixmap().width(); }

    QString name;

    enum { Type = UserType + 1 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
};

#endif // CARD_H
