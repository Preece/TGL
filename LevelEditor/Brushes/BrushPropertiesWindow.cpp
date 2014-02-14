#include "BrushPropertiesWindow.h"
#include "ui_BrushPropertiesWindow.h"

BrushPropertiesWindow::BrushPropertiesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushPropertiesWindow)
{
    ui->setupUi(this);

    resourceManager = NULL;
    currentBrush = NULL;
    tileSelector = NULL;

    currentListIndex = 0;

    ui->tileList->setScene(&tileList);

    ui->smartBrushButtons->setId(ui->topLeft, 0);
    ui->smartBrushButtons->setId(ui->topMiddle, 1);
    ui->smartBrushButtons->setId(ui->topRight, 2);
    ui->smartBrushButtons->setId(ui->middleLeft, 3);
    ui->smartBrushButtons->setId(ui->middle, 4);
    ui->smartBrushButtons->setId(ui->middleRight, 5);
    ui->smartBrushButtons->setId(ui->bottomLeft, 6);
    ui->smartBrushButtons->setId(ui->bottomMiddle, 7);
    ui->smartBrushButtons->setId(ui->bottomRight, 8);
    ui->smartBrushButtons->setId(ui->topLeftCorner, 9);
    ui->smartBrushButtons->setId(ui->topRightCorner, 10);
    ui->smartBrushButtons->setId(ui->bottomLeftCorner, 11);
    ui->smartBrushButtons->setId(ui->bottomRightCorner, 12);

    connect(ui->smartBrushButtons, SIGNAL(buttonClicked(int)), this, SLOT(SmartButtonPushed()));
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

void BrushPropertiesWindow::NewBrush(ComplexBrush *newBrush)
{
    //clear out the tile list
    tileList.clear();

    currentBrush = NULL;

    //empty the name input
    ui->brushNameInput->setText("");

    currentBrush = newBrush;
}

void BrushPropertiesWindow::EditBrush(ComplexBrush *editBrush)
{
    currentBrush = editBrush;

    ui->brushNameInput->setText(currentBrush->GetName());

    RepopulateTileList();
}

void BrushPropertiesWindow::ShowScatterControls()
{
    ui->smartBrushGroup->hide();
    ui->replacerBrushGroup->hide();
    SetListIndex(0);
}

void BrushPropertiesWindow::ShowSmartControls()
{
    ui->smartBrushGroup->setTitle("Smart Brush");
    ui->smartBrushGroup->show();
    ui->replacerBrushGroup->hide();
    SetListIndex(4);
}

void BrushPropertiesWindow::ShowReplacerControls()
{
    ui->smartBrushGroup->hide();
    ui->replacerBrushGroup->show();
    SetListIndex(1);
}

void BrushPropertiesWindow::ShowMatrixControls()
{
    ui->smartBrushGroup->setTitle("Matrix Brush");
    ui->smartBrushGroup->show();
    ui->replacerBrushGroup->hide();
    SetListIndex(4);
}

void BrushPropertiesWindow::on_addTile_clicked()
{
    if(currentBrush)
    {
        currentBrush->AddTile(currentListIndex, GetSelectedTileID());
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
        TileWidgetItem *tempItem = dynamic_cast<TileWidgetItem*>(tileSelector->selectedItems()[0]);

        if(tempItem)
            return tempItem->GetTileID();
    }

    return 0;
}

TileWidgetItem *BrushPropertiesWindow::GetSelectedTile()
{
    if(IsTileSelected())
    {
        return dynamic_cast<TileWidgetItem*>(tileSelector->selectedItems()[0]);
    }

    return NULL;
}

TileWidgetItem *BrushPropertiesWindow::GetTileFromID(int ID)
{
    TileWidgetItem *tempItem = new TileWidgetItem;

    tempItem->SetTile(resourceManager->GetTile(ID));
    tempItem->setPixmap(resourceManager->GetTilePixmap(ID));

    return tempItem;
}

bool BrushPropertiesWindow::IsListTileSelected()
{
    if(tileList.selectedItems().count() > 0)
        return true;

    return false;
}

int BrushPropertiesWindow::GetSelectedListTileIndex()
{
    if(!IsListTileSelected())
        return -1;

    TileWidgetItem *tempTile =  static_cast<TileWidgetItem*>(tileList.selectedItems()[0]);

    if(tempTile)
        return tempTile->GetIndex();

    return -1;
}

void BrushPropertiesWindow::RepopulateTileList()
{
    tileList.clear();

    //make sure there is a brush
    if(currentBrush)
    {
        //loop through all of the current scatter brushes tiles
        for(int i = 0; i < currentBrush->GetTileCount(currentListIndex); i++)
        {
            //create a visible item for each one, and set its position
            TileWidgetItem *tempItem = GetTileFromID(currentBrush->GetTile(currentListIndex, i));
            tempItem->setPos((i * resourceManager->GetLevelProperties()->GetTileWidth()) + i, 0);
            tempItem->setFlag(QGraphicsItem::ItemIsSelectable);
            tempItem->SetIndex(i);

            //add the new tile to the tile list
            tileList.addItem(tempItem);
        }
    }
}

void BrushPropertiesWindow::on_brushNameInput_textChanged(const QString &arg1)
{
    if(currentBrush)
    {
        currentBrush->SetName(arg1);
    }
}

void BrushPropertiesWindow::on_buttonBox_accepted()
{
    if(currentBrush)
        if(currentBrush->GetName() == "")
        {
            currentBrush->SetName("New Brush");
        }
}

void BrushPropertiesWindow::SmartButtonPushed()
{
    //the button IDs correspond to the list index
    currentListIndex = ui->smartBrushButtons->checkedId();

    RepopulateTileList();
}

void BrushPropertiesWindow::on_removeTile_clicked()
{
    if(IsListTileSelected())
    {
        currentBrush->RemoveTile(currentListIndex, GetSelectedListTileIndex());
        RepopulateTileList();
    }
}

void BrushPropertiesWindow::on_dirtyTilesButton_clicked()
{
    currentListIndex = 1;
    RepopulateTileList();
}

void BrushPropertiesWindow::on_cleanTilesButton_clicked()
{
    currentListIndex = 0;
    RepopulateTileList();
}
