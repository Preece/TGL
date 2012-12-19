#include "BrushPropertiesWindow.h"
#include "ui_BrushPropertiesWindow.h"

BrushPropertiesWindow::BrushPropertiesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushPropertiesWindow)
{
    ui->setupUi(this);

    resourceManager = NULL;
    currentScatterBrush = NULL;
    tileSelector = NULL;
    ui->tileList->setScene(&tileList);
}

BrushPropertiesWindow::~BrushPropertiesWindow()
{
    delete ui;
}

void BrushPropertiesWindow::RegisterTileSelector(QGraphicsScene *selector)
{
    ui->tileSelector->setScene(selector);
    tileSelector = selector;
}

void BrushPropertiesWindow::NewScatterBrush(ScatterBrush *newBrush)
{
    //clear out the tile list
    tileList.clear();

    currentScatterBrush = NULL;

    //empty the name input
    ui->brushNameInput->setText("");

    currentScatterBrush = newBrush;
}

void BrushPropertiesWindow::EditScatterBrush(ScatterBrush *editBrush)
{
    currentScatterBrush = editBrush;

    ui->brushNameInput->setText(currentScatterBrush->GetName());

    RepopulateTileList();
}

void BrushPropertiesWindow::on_addTile_clicked()
{
    if(currentScatterBrush)
    {
        currentScatterBrush->AddTile(GetSelectedTileID());
        RepopulateTileList();
    }
}

bool BrushPropertiesWindow::IsTileSelected()
{
    if(!tileSelector)
        return false;

    if(tileSelector->selectedItems().count() > 0)
        return true;

    return false;
}

int BrushPropertiesWindow::GetSelectedTileID()
{
    if(IsTileSelected())
    {
        TileItem *tempItem = dynamic_cast<TileItem*>(tileSelector->selectedItems()[0]);

        if(tempItem)
            return tempItem->GetTileID();
    }

    return 0;
}

TileItem *BrushPropertiesWindow::GetSelectedTile()
{
    if(IsTileSelected())
    {
        return dynamic_cast<TileItem*>(tileSelector->selectedItems()[0]);
    }

    return NULL;
}

TileItem *BrushPropertiesWindow::GetTileFromID(int ID)
{
    TileItem *tempItem = new TileItem;

    tempItem->SetTile(resourceManager->GetTile(ID));
    tempItem->setPixmap(resourceManager->GetTilePixmap(ID));

    return tempItem;
}

void BrushPropertiesWindow::RepopulateTileList()
{
    tileList.clear();

    //make sure there is a brush
    if(currentScatterBrush)
    {
        //loop through all of the current scatter brushes tiles
        for(int i = 0; i < currentScatterBrush->GetTileCount(); i++)
        {
            //create a visible item for each one, and set its position
            TileItem *tempItem = GetTileFromID(currentScatterBrush->GetTile(i));
            tempItem->setPos((i * resourceManager->GetLevelProperties()->GetTileWidth()) + i, 0);

            //add the new tile to the tile list
            tileList.addItem(tempItem);
        }
    }
}

void BrushPropertiesWindow::on_brushNameInput_textChanged(const QString &arg1)
{
    if(currentScatterBrush)
    {
        currentScatterBrush->SetName(arg1);
    }
}

void BrushPropertiesWindow::on_buttonBox_accepted()
{
    if(currentScatterBrush)
        if(currentScatterBrush->GetName() == "")
        {
            currentScatterBrush->SetName("New Scatter Brush");
        }
}
