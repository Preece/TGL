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
    SetListIndex(0);
}

void BrushPropertiesWindow::ShowSmartControls()
{
    ui->smartBrushGroup->show();
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
    if(currentBrush)
    {
        //loop through all of the current scatter brushes tiles
        for(int i = 0; i < currentBrush->GetTileCount(currentListIndex); i++)
        {
            //create a visible item for each one, and set its position
            TileItem *tempItem = GetTileFromID(currentBrush->GetTile(currentListIndex, i));
            tempItem->setPos((i * resourceManager->GetLevelProperties()->GetTileWidth()) + i, 0);

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
