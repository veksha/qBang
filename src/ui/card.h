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
                , selected(false)
    {
        setCacheMode(DeviceCoordinateCache);
        this->name = name;
        setObjectName(name);
        SetOncomingPosition(pos());
    }
    
    enum { Type = UserType + 1 };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    
    int GetHeight() { return pixmap().height(); }
    int GetWidth() { return pixmap().width(); }
    
    QPointF GetPosition() { return pos(); }
    QPointF GetOncomingPosition() { return oncomingPos; }
    void SetOncomingPosition(QPointF value) { oncomingPos = value; }
    
    QString GetName() { return name; }
    void SetPixmap(const QPixmap& pixmap) { setPixmap(pixmap); }
    bool GetSelected() { return selected; }
    void SetSelected(bool value) { selected = value; }

private:
    QString name;
    bool selected;
    QPointF oncomingPos;
};

#endif // CARD_H
