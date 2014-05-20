#include "TileController.h"

TileController::TileController(QObject *parent) :
    QObject(parent)
{
    modifyTiles = new ModifyTilesCommand();
    currentLayer = NULL;
    resources = NULL;

    connect(modifyTiles, SIGNAL(RepaintTile(int,int,int,TileCoord)), this, SIGNAL(TileUpdated(int,int,int,TileCoord)));
}

TileController::~TileController()
{
    if(modifyTiles)
        delete modifyTiles;
}

int TileController::GetTileWidth()
{
    return resources->GetTileWidth();
}

int TileController::GetTileHeight()
{
    return resources->GetTileHeight();
}

int TileController::GetCurrentLayerWidth()
{
    if(currentLayer)
        return currentLayer->GetWidth();

    return 0;
}

int TileController::GetCurrentLayerHeight()
{
    if(currentLayer)
        return currentLayer->GetHeight();

    return 0;
}

void TileController::UpdateLayerVisibility(bool visible)
{
    if(currentLayer)
    {
        currentLayer->SetVisibility(visible);
        emit LayerVisibilityUpdated(currentLayer->GetID(), visible);
    }
}

void TileController::ModifyTile(int x, int y, TileCoord origin)
{
    if(currentLayer)
    {
        //make sure the point will fit in the layer
        if(!currentLayer->ResizeToIncludePoint(x, y))
            return;

        emit LayerSizeUpdated(currentLayer->GetWidth(), currentLayer->GetHeight());

        modifyTiles->AddModification(currentLayer, x, y, origin, currentLayer->GetTileOrigin(x, y));

        //notify the view that this tile should be updated
        emit TileUpdated(currentLayer->GetID(), x, y, origin);
    }
}

void TileController::PreviewModifyTile(int x, int y, TileCoord origin)
{
    if(currentLayer)
        if(!currentLayer->PointIsWithinLayer(x, y))
            return;

    if(previewTiles.contains(TileCoord(x, y)))
    {
        if(previewTiles[TileCoord(x, y)].origin == origin)
            return;
    }

    if(origin != TileCoord(-1, -1))
    {
        Tile tempTile;
        tempTile.origin = origin;
        tempTile.pos = TileCoord(x, y);
        previewTiles[TileCoord(x, y)] = tempTile;
    }
    else
    {
        previewTiles.remove(TileCoord(x, y));
    }

    emit PreviewTileUpdated(x, y, origin);
}

void TileController::ClearPreview()
{
    QList<Tile> previewList = previewTiles.values();
    for(int i = 0; i < previewList.count(); i++)
    {
        PreviewModifyTile(previewList[i].pos.first, previewList[i].pos.second, TileCoord(-1, -1));
    }

    //previewTiles.clear();
}

TileCoord TileController::GetTileOrigin(int x, int y)
{
    //see if there is an upcoming modification to this tile
    TileCoord modOrigin = modifyTiles->GetTileOrigin(x, y);
    if(modOrigin != TileCoord(-1, -1))
        return modOrigin;

    if(currentLayer)
        return currentLayer->GetTileOrigin(x, y);

    return TileCoord(-1, -1);
}

void TileController::SelectTilesInArea(QRect area)
{
    if(area.left() > area.right())
    {
        int temp = area.left();
        area.setLeft(area.right());
        area.setRight(temp);
    }

    if(area.top() > area.bottom())
    {
        int temp = area.top();
        area.setTop(area.bottom());
        area.setBottom(temp);
    }

    selectionArea = area.normalized();

    emit SelectionGeometryUpdated(area);
}

QList<Tile> TileController::GetSelectedTiles()
{
    QList<Tile> selectedTiles;

    for(int i = selectionArea.left(); i <= selectionArea.right(); i++)
    {
        for(int j = selectionArea.top(); j <= selectionArea.bottom(); j++)
        {
            TileCoord origin = GetTileOrigin(i, j);

            if(origin != TileCoord(-1, -1))
            {
                Tile tempTile;
                tempTile.pos.first = i;
                tempTile.pos.second = j;
                tempTile.origin = origin;
                selectedTiles.append(tempTile);
            }
        }
    }

    return selectedTiles;
}

void TileController::ClearSelection()
{

}

int TileController::GetLayerOpacity(int layerID)
{
    if(currentLayer)
        return currentLayer->GetOpacity();

    return 100;
}

QPixmap TileController::GetTilePixmap(TileCoord coord)
{
    return resources->GetTilePixmap(coord);
}


void TileController::UpdateLayerSelection(int newLayer)
{
    currentLayer = resources->GetTileLayer(newLayer);
}

void TileController::EndPaintOperation()
{
    //if there are no changes that occured, no undo operation needs to be processed
    if(modifyTiles->GetModificationCount() == 0)
        return;

    //push the current bundle of modifications into the undo stack
    resources->AddUndoCommand(modifyTiles);

    //create a fresh bundle for the next operation
    modifyTiles = new ModifyTilesCommand;

    connect(modifyTiles, SIGNAL(RepaintTile(int,int,int,TileCoord)), this, SIGNAL(TileUpdated(int,int,int,TileCoord)));
}
