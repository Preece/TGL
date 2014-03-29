#ifndef FRAME_H
#define FRAME_H

#include <QRect>
#include <QPoint>
#include <QList>

#include "ItemNode.h"

class Frame : public ItemNode
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "FRME"; }

    Frame();
    ~Frame();

    void SetFrameRect(QRect newFrameRect) { frameRect = newFrameRect; }
    QRect GetFrameRect() { return frameRect; }

    void SetDelay(int newDelay) { delay = newDelay; }
    int GetDelay() {return delay; }

    void SetRenderSpot(QPoint newRenderSpot) { renderSpot = newRenderSpot; }
    QPoint GetRenderSpot() { return renderSpot; }

    void SetBoundingBoxXY(QPoint newXY) { boundingBoxXY = newXY; }
    QPoint GetBoundingBoxXY() { return boundingBoxXY; }

    void AddHotspot(QPoint newHotspot) { hotspots.push_back(newHotspot); }
    QPoint GetHotspot(int index) { return hotspots[index]; }
    void RemoveHotspot(int index) { hotspots.removeAt(index); }

private:
    QRect frameRect;
    int delay;

    QPoint renderSpot;
    QPoint boundingBoxXY;

    QList<QPoint> hotspots;

};

#endif // FRAME_H
