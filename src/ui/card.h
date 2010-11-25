#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <include/plugininterface.h>

class Card: public QObject, public QGraphicsPixmapItem, public AbstractCard
{
    Q_OBJECT
    Q_INTERFACES(AbstractCard)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
            Card(const QString &name, QPixmap pix): QObject(), QGraphicsPixmapItem(pix)
    {
        setCacheMode(DeviceCoordinateCache);
        this->name = name;
        setObjectName(name);
    }
    
    int GetHeight() { return pixmap().height(); }
    int GetWidth() { return pixmap().width(); }
    QString GetName() { return name; }

private:
    QString name;

    enum { Type = UserType + 1 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
};

#endif // CARD_H
