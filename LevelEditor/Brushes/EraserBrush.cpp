#include "EraserBrush.h"

EraserBrush::EraserBrush()
{
}

/*void LayerManager::EraseTile(QPoint pos)
{
    if(!resourceManager || !currentTile || !currentLayer)
        return;

    if(resourceManager->GetLevelProperties()->IsPropertiesSet())
    {
        //translate the position to tile coordinates
        int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
        int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

        int tileX = pos.x() / tileW;
        int tileY = pos.y() / tileH;

        //if the position is beyond the bounds of the scene, ignore it
        //EVENTUALLY THE PARALLAX WILL NEED TO BE CONSIDERED
        if(tileX >= resourceManager->GetLevelProperties()->GetMapWidth() ||
           tileY >= resourceManager->GetLevelProperties()->GetMapHeight())
            return;

        //modify the correct tiles tileID to the one of the selection
        Layer *currentModelLayer = resourceManager->GetLayer(currentLayer->GetLayerID());

        if(currentModelLayer)
        {
            currentModelLayer->ModifyTile(tileX, tileY, 0);
        }

        RepopulateLayer(currentLayer);
    }
}*/
