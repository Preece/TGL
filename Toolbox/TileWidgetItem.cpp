#include "TileWidgetItem.h"

TileWidgetItem::TileWidgetItem()
{
    index = 0;
    origin.first = -1;
    origin.second = -1;

    setCacheMode(QGraphicsItem::ItemCoordinateCache);
}

TileWidgetItem::~TileWidgetItem()
{
}

void TileWidgetItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionGraphicsItem myOption(*option);

    if(myOption.state & QStyle::State_Selected)
    {
        //unset the selected flag so the default selection stuff isnt drawn
        myOption.state &= ~QStyle::State_Selected;

        //paint the tile
        QGraphicsPixmapItem::paint(painter, &myOption, widget);

        //now paint the custom selection shit on top
        QBrush newBrush(QColor(Qt::black), Qt::BDiagPattern);
        QPen newPen(Qt::transparent);

        painter->setBrush(newBrush);
        painter->setPen(newPen);
        painter->drawRect(option->exposedRect);
    }
    else
    {
        QGraphicsPixmapItem::paint(painter, option, widget);
    }

}

void TileWidgetItem::SetTilePixmap(QPixmap newPix)
{
    setPixmap(newPix);
}
