#include "BrushPropertiesDialog.h"
#include "ui_BrushPropertiesDialog.h"

BrushPropertiesDialog::BrushPropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushPropertiesDialog)
{
    ui->setupUi(this);

    resourceController = NULL;
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

BrushPropertiesDialog::~BrushPropertiesDialog()
{
    delete ui;
}

void BrushPropertiesDialog::RegisterTileSelector(TileSelectorScene *selector)
{
    ui->tileSelector->setScene(selector);
    tileSelector = selector;
}

void BrushPropertiesDialog::NewBrush(ComplexBrush *newBrush)
{
    //clear out the tile list
    tileList.clear();

    currentBrush = NULL;

    //empty the name input
    ui->brushNameInput->setText("");

    currentBrush = newBrush;
}

void BrushPropertiesDialog::EditBrush(ComplexBrush *editBrush)
{
    currentBrush = editBrush;

    ui->brushNameInput->setText(currentBrush->GetName());

    RepopulateTileList();
}

void BrushPropertiesDialog::ShowScatterControls()
{
    ui->smartBrushGroup->hide();
    ui->replacerBrushGroup->hide();
    SetListIndex(0);
}

void BrushPropertiesDialog::ShowSmartControls()
{
    ui->smartBrushGroup->setTitle("Smart Brush");
    ui->smartBrushGroup->show();
    ui->replacerBrushGroup->hide();
    SetListIndex(4);
}

void BrushPropertiesDialog::ShowReplacerControls()
{
    ui->smartBrushGroup->hide();
    ui->replacerBrushGroup->show();
    SetListIndex(1);
}

void BrushPropertiesDialog::ShowMatrixControls()
{
    ui->smartBrushGroup->setTitle("Matrix Brush");
    ui->smartBrushGroup->show();
    ui->replacerBrushGroup->hide();
    SetListIndex(4);
}

void BrushPropertiesDialog::on_addTile_clicked()
{
    if(currentBrush)
    {
        currentBrush->AddTiles(currentListIndex, tileSelector->GetSelectedTiles());
        RepopulateTileList();
    }
}

bool BrushPropertiesDialog::IsTileSelected()
{
    if(!tileSelector)
        return false;

    if(tileSelector->selectedItems().count() > 0)
        return true;

    return false;
}

TileWidgetItem *BrushPropertiesDialog::GetSelectedTile()
{
    if(IsTileSelected())
    {
        return dynamic_cast<TileWidgetItem*>(tileSelector->selectedItems()[0]);
    }

    return NULL;
}

TileWidgetItem *BrushPropertiesDialog::GetTileFromOrigin(TileCoord coord)
{
    TileWidgetItem *tempItem = new TileWidgetItem;

    tempItem->setPixmap(resourceController->GetTilePixmap(coord));

    return tempItem;
}

bool BrushPropertiesDialog::IsListTileSelected()
{
    if(tileList.selectedItems().count() > 0)
        return true;

    return false;
}

int BrushPropertiesDialog::GetSelectedListTileIndex()
{
    if(!IsListTileSelected())
        return -1;

    TileWidgetItem *tempTile =  static_cast<TileWidgetItem*>(tileList.selectedItems()[0]);

    if(tempTile)
        return tempTile->GetIndex();

    return -1;
}

void BrushPropertiesDialog::RepopulateTileList()
{
    tileList.clear();

    //make sure there is a brush
    if(currentBrush)
    {
        //loop through all of the current scatter brushes tiles
        for(int i = 0; i < currentBrush->GetTileCount(currentListIndex); i++)
        {
            //create a visible item for each one, and set its position
            TileWidgetItem *tempItem = GetTileFromOrigin(currentBrush->GetTile(currentListIndex, i));
            tempItem->setPos((i * resourceController->GetTileWidth()) + i, 0);
            tempItem->setFlag(QGraphicsItem::ItemIsSelectable);
            tempItem->SetIndex(i);

            //add the new tile to the tile list
            tileList.addItem(tempItem);
        }
    }
}

void BrushPropertiesDialog::on_brushNameInput_textChanged(const QString &arg1)
{
    if(currentBrush)
    {
        currentBrush->SetName(arg1);
    }
}

void BrushPropertiesDialog::on_buttonBox_accepted()
{
    if(currentBrush)
        if(currentBrush->GetName() == "")
        {
            currentBrush->SetName("New Brush");
        }
}

void BrushPropertiesDialog::SmartButtonPushed()
{
    //the button IDs correspond to the list index
    currentListIndex = ui->smartBrushButtons->checkedId();

    RepopulateTileList();
}

void BrushPropertiesDialog::on_removeTile_clicked()
{
    if(IsListTileSelected())
    {
        currentBrush->RemoveTile(currentListIndex, GetSelectedListTileIndex());
        RepopulateTileList();
    }
}

void BrushPropertiesDialog::on_dirtyTilesButton_clicked()
{
    currentListIndex = 1;
    RepopulateTileList();
}

void BrushPropertiesDialog::on_cleanTilesButton_clicked()
{
    currentListIndex = 0;
    RepopulateTileList();
}
