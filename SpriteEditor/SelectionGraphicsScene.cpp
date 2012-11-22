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
    renderSpot->show();

    this->addItem(selectionBox);
    this->addItem(renderSpot);

    currentTool = 0;
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
    else if(mouseEvent->buttons() == Qt::LeftButton && currentTool == 3)
    {
        if(!selectionBox->rect().isNull())
        {
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

            renderSpot->setPos(pressSpot.x(), pressSpot.y());
            renderSpot->show();

            //emit a signal that the renderspot has been moved
            emit RenderSpotUpdated(renderSpot->scenePos().toPoint());
        }
    }
}

void SelectionGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //if a regular frame drag is released
    if(mouseEvent->button() == Qt::LeftButton && currentTool == 0)
        //signal that a new rect is ready
        emit SelectionUpdated(selectionBox->rect().toRect());

    //if the auto frame select is used
    if(mouseEvent->button() == Qt::LeftArrow && currentTool == 1)
    {
        AutoSelectFrame(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    }
}

void SelectionGraphicsScene::UpdateSelectionRect(QRect newRect)
{
    //set the rectangle of the selection box to the specified rect
    selectionBox->setRect(newRect);
}

void SelectionGraphicsScene::UpdateRenderSpot(QPoint newSpot)
{
    renderSpot->setPos(newSpot.x(), newSpot.y());
    renderSpot->show();
}

void SelectionGraphicsScene::AutoSelectFrame(int x, int y)
{
    //if a spritesheet is loaded
        //get the spritesheet

        //get the color of the top left pixel

        //if the pixel at the specified coordinates is the key color, return

        //if not
            //loop while the selection box is smaller than the image
                //check if the right border is all the key color
                    //if not, push that border by 1 pixel
                //check if the bottom border is all the key color
                    //if not, push the border by 1 pixel
                //check the left
                    //push the border
                //check the top
    //push the border
}
