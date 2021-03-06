#ifndef MODIFYTILESCOMMAND_H
#define MODIFYTILESCOMMAND_H

#include <QObject>
#include <QUndoCommand>
#include <QMultiMap>

#include "../TileLayer.h"

//this class should collect modifications with am AddModification function.
//Then, the redo function will actually implement all those changes.
//The modifications themselves will indicate whether they added a tile, or
//changed an existing one. The undo function will trawl backwards through
//the list, doing the inverse operations on each modification

struct TileModification
{
	TileLayer *layer;
    int x, y;
    TileCoord newOrigin;
    TileCoord oldOrigin;
};

class ModifyTilesCommand : public QObject, public QUndoCommand
{
    Q_OBJECT

public:
    explicit ModifyTilesCommand(QObject *parent = 0);
    ~ModifyTilesCommand();

    void AddModification(TileLayer *layer, int newX, int newY, TileCoord newOrgn, TileCoord oldOrgn);
    int GetModificationCount();

    TileCoord GetTileOrigin(int x, int y);

    void undo();
    void redo();

signals:
    void RepaintTile(int layerID, int x, int y, TileCoord newOrigin);

private:

    QHash<TileCoord, TileModification> mods;
    bool initialRedo;
};

#endif // MODIFYTILESCOMMAND_H
