#include "Frame.h"

bool Frame::Export(Exporter *exporter)
{
    exporter->WriteRect(frameRect);
    exporter->WriteInt(delay);
    exporter->WritePoint(renderSpot);
    exporter->WritePoint(boundingBoxXY);

    exporter->WriteInt(hotspots.count());
    for(int i = 0; i < hotspots.count(); i++)
        exporter->WritePoint(hotspots[i]);

    return true;
}

bool Frame::Import(Exporter *exporter)
{
    exporter->ReadRect(frameRect);
    exporter->ReadInt(delay);
    exporter->ReadPoint(renderSpot);
    exporter->ReadPoint(boundingBoxXY);

    int hotspotCount;
    exporter->ReadInt(hotspotCount);
    for(int i = 0; i < hotspotCount; i++)
        exporter->ReadPoint(hotspots[i]);

    return true;
}

Frame::Frame()
{
    delay = 100;
}

Frame::~Frame()
{
}
