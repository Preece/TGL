#ifndef REPLACERBRUSH_H
#define REPLACERBRUSH_H

#include "ComplexBrush.h"

class ReplacerBrush : public ComplexBrush
{
public:
    ReplacerBrush();

    void Paint(int x, int y, ResourceManager *resources, bool preview);

    QString GetType() { return "replacer"; }
};

#endif // REPLACERBRUSH_H
