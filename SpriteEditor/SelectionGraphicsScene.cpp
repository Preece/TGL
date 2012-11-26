#include "SelectionGraphicsScene.h"

SelectionGraphicsScene::SelectionGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    //create the selection box and assign it to the scene
    selectionBox = new QGraphicsRectItem();

    //set the properties of the selection box
    selectionBox->setPen(QPen(Qt::DashLine));
    selectionBox->setZValue(99);
    selectionBox->show();

    renderSpot = new QGraphicsPixmapItem(QPixmap(":/Icons/Icons/renderspot.png"));
    renderSpot->setOffset(-7, -7);
    renderSpot->setZValue(100);
    renderSpot->setParentItem(selectionBox);
    renderSpot->setPos(0, 0);
    renderSpot->hide();

    this->addItem(selectionBox);
    //this->addItem(renderSpot);

    currentTool = 1;
}

SelectionGraphicsScene::~SelectionGraphicsScene()
{
}

void SelectionGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons() == Qt::LeftButton && currentTool == 0)
    {
        //set the rect of the selection box based on the new position and the origin
        QPoint tempPoint = mouseEvent->lastScenePos().toPoint();

        //if the new point exceeds the size of the scene
        if(tempPoint.x() > this->width())
            //reign in the size so it fits
            tempPoint.setX(this->width() - 1);

        if(tempPoint.y() > this->height())
            tempPoint.setY(this->height() - 1);

        //if the box is inverted, make it 1x1
        if(tempPoint.x() < origin.x())
            tempPoint.setX(origin.x() + 1);
        if(tempPoint.y() < origin.y())
            tempPoint.setY(origin.y() + 1);


        selectionBox->setRect(origin.x(), origin.y(), tempPoint.x() - origin.x(), tempPoint.y() - origin.y());
    }
}

void SelectionGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //frame select
    if(mouseEvent->buttons() == Qt::LeftButton && currentTool == 0)
    {
        //nullify the dimensions of the selection
        selectionBox->setRect(0, 0, 0, 0);

        //capture the point that was clicked
        origin = mouseEvent->buttonDownScenePos(Qt::LeftButton).toPoint();

        //make sure the origin is inside the image
        if(origin.x() < 0)
            origin.setX(0);
        if(origin.x() > this->width())
            origin.setX(this->width() - 2);
        if(origin.y() < 0)
            origin.setY(0);
        if(origin.y() > this->height())
            origin.setY(this->height() - 2);

    }
    //auto frame select
    else if(mouseEvent->buttons() == Qt::LeftButton && currentTool == 1)
    {
        QPoint pressSpot = mouseEvent->buttonDownScenePos(Qt::LeftButton).toPoint();

        AutoSelectFrame(pressSpot.x(), pressSpot.y());
        UpdateRenderSpot(QPoint(0, 0));
        renderSpot->show();
    }
    //render spot
    else if(mouseEvent->buttons() == Qt::LeftButton && currentTool == 3)
    {
        if(!selectionBox->rect().isNull())
        {
            //show the render spot
            renderSpot->show();

            //position the render spot item at the mouse
            QPoint pressSpot = mouseEvent->buttonDownScenePos(Qt::LeftButton).toPoint();

            //make sure that the render spot is inside the frame
            if(pressSpot.x() < selectionBox->rect().left())
                pressSpot.setX(selectionBox->rect().left());
            if(pressSpot.x() > selectionBox->rect().right())
                pressSpot.setX(selectionBox->rect().right());
            if(pressSpot.y() < selectionBox->rect().top())
                pressSpot.setY(selectionBox->rect().top());
            if(pressSpot.y() > selectionBox->rect().bottom())
                pressSpot.setY(selectionBox->rect().bottom());

            //transform to item coordinates
            pressSpot.setX(pressSpot.x() - selectionBox->rect().x());
            pressSpot.setY(pressSpot.y() - selectionBox->rect().y());

            UpdateRenderSpot(pressSpot);
            renderSpot->show();

            //emit a signal that the renderspot has been moved
            emit RenderSpotUpdated(pressSpot);
        }
    }
}

void SelectionGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //if a regular frame drag is released
    if(mouseEvent->button() == Qt::LeftButton && currentTool == 0)
    {
        //signal that a new rect is ready
        emit SelectionUpdated(selectionBox->rect().toRect());

        UpdateRenderSpot(QPoint(0, 0));
        renderSpot->show();
    }
}

void SelectionGraphicsScene::UpdateSelectionRect(QRect newRect)
{
    //set the rectangle of the selection box to the specified rect
    selectionBox->setRect(newRect);

    if(newRect.isNull())
        renderSpot->hide();
    else
        renderSpot->show();
}

void SelectionGraphicsScene::UpdateRenderSpot(QPoint newSpot)
{
    //this translates from relative to absolute coordinates
    renderSpot->setPos(newSpot.x() + selectionBox->rect().x(), newSpot.y() + selectionBox->rect().y());
    renderSpot->show();
}

void SelectionGraphicsScene::AutoSelectFrame(int x, int y)
{
    //check that the value is in bounds of the image
    if(x < 0 || y < 0 || x >= spritesheet.width() || y >= spritesheet.height())
        return;

    //if a spritesheet is loaded
    if(!spritesheet.isNull())
    {
        //get the color of the top left pixel
        QRgb colorKey = spritesheet.pixel(0, 0);

        //if the pixel at the specified coordinates is the key color, return
        if(colorKey == spritesheet.pixel(x, y))
            return;

        //if not
        else
        {
            int expanding;
            QRect newSelection(x - 1, y - 1, 2, 2);

            //loop while the selection box is smaller than the image and the box is expanding
            while((newSelection.width() * newSelection.height()) < (spritesheet.rect().width() * spritesheet.rect().height()) && expanding)
            {
                expanding = 0;

                //check if the right border is all the key color
                for(int i = 0; i < newSelection.height(); i++)
                {
                    //if the pixel along the right border does not equal the color key
                    if(spritesheet.pixel(newSelection.right(), newSelection.top() + i) != colorKey)
                    {
                        //if the edge is pushing against the right border
                        if(newSelection.right() == spritesheet.rect().right())
                            break;

                        //push the right border over by one
                        newSelection.setRight(newSelection.right() + 1);

                        //the selection is still expanding
                        expanding++;

                        //and break out of the loop
                        break;
                    }
                }

                //check if the bottom border is all the key color
                for(int i = 0; i < newSelection.width(); i++)
                {
                    //if the pixel along the bottom border does not equal the color key
                    if(spritesheet.pixel(newSelection.left() + i, newSelection.bottom()) != colorKey)
                    {
                        //if the edge is pushing against the bottom border
                        if(newSelection.bottom() == spritesheet.rect().bottom())
                            break;

                        //push the bottom border down by one
                        newSelection.setBottom(newSelection.bottom() + 1);

                        //the selection is still expanding
                        expanding++;

                        //and break out of the loop
                        break;
                    }
                }

                //check the left
                for(int i = 0; i < newSelection.height(); i++)
                {
                    //if the pixel along the right border does not equal the color key
                    if(spritesheet.pixel(newSelection.left(), newSelection.top() + i) != colorKey)
                    {
                        //if the edge is pushing against the left border
                        if(newSelection.left() == 0)
                            break;

                        //push the right border over by one
                        newSelection.setLeft(newSelection.left() - 1);

                        //the selection is still expanding
                        expanding++;

                        //and break out of the loop
                        break;
                    }
                }


                //check the top
                for(int i = 0; i < newSelection.width(); i++)
                {
                    //if the pixel along the top border does not equal the color key
                    if(spritesheet.pixel(newSelection.left() + i, newSelection.top()) != colorKey)
                    {
                        //if the edge is pushing against the top border
                        if(newSelection.top() == 0)
                            break;

                        //push the top border up by one
                        newSelection.setTop(newSelection.top() - 1);

                        //the selection is still expanding
                        expanding++;

                        //and break out of the loop
                        break;
                    }
                }
            }

            selectionBox->setRect(newSelection);

            //signal that a new rect is ready
            emit SelectionUpdated(selectionBox->rect().toRect());
        }
    }
}
