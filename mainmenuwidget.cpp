#include "mainmenuwidget.h"

#include "mainmenucontroller.h"

MainMenuWidget::MainMenuWidget()
{
    this->resize(500, 500);
    QVBoxLayout * layout = new QVBoxLayout(this);
    QHBoxLayout * hlayout1 = new QHBoxLayout();
    QHBoxLayout * hlayout2 = new QHBoxLayout();

    playButton.setText("PLAY");
    optionsButton.setText("OPTIONS");
    levelEditorButton.setText("MAP EDITOR");
    loadLevelButton.setText("LOAD LEVEL");

    QLabel * label = new QLabel;
    label->setPixmap(QPixmap(":/resources/graphics/welcome.png").scaled(520, 200));

    //listWidget style
    applyStyleSheet();

    //Add element in layout
    layout->addWidget(label);
    layout->addWidget(&listWidget);

    layout->addLayout(hlayout1);
    hlayout1->addWidget(&playButton);
    hlayout1->addWidget(&optionsButton);

    layout->addLayout(hlayout2);
    hlayout2->addWidget(&levelEditorButton);
    hlayout2->addWidget(&loadLevelButton);

    //Connect the buttons to their slots
    connect(&playButton, SIGNAL (clicked()), this, SLOT (handlePlayButton()));
    connect(&optionsButton, SIGNAL (clicked()), this, SLOT (handleOptionsButton()));
    connect(&levelEditorButton, SIGNAL (clicked()), this, SLOT (handleLevelEditorButton()));
    connect(&loadLevelButton, SIGNAL (clicked()), this, SLOT (handleLoadLevelButton()));
}

void MainMenuWidget::applyStyleSheet()
{
    listWidget.setStyleSheet("background-color: black;"
                              "color: white;"
                              "font-size: 20px;"
                              "font-weight : bold;");

    QString styleButton = "QPushButton {background-color: #BE2801;"
                          "color: white;"
                          "font-size: 20px;"
                          "font-weight : bold;}"
                          ""
                          "QPushButton:hover {background-color: white;"
                          "color: #BE2801;"
                          "font-size: 20px;"
                          "font-weight : bold;}";


    setStyleSheet(styleButton);
}

void MainMenuWidget::addItemToWidgetList(QString text, QString address)
{
    QListWidgetItem * qListWidgetItem = new QListWidgetItem();
    qListWidgetItem->setData(Qt::UserRole, address);
    qListWidgetItem->setText(text);
    listWidget.addItem(qListWidgetItem);

    //Keep the first row of the list selected
    listWidget.setCurrentRow(0);
}

void MainMenuWidget::handlePlayButton()
{
    mainMenuController->launchGameOnMainWindow(listWidget.currentItem()->data(Qt::UserRole).toString());
}

void MainMenuWidget::handleOptionsButton()
{
    mainMenuController->launchOptionsMenuOnMainWindow();
}

void MainMenuWidget::handleLoadLevelButton()
{
    mainMenuController->addLevelToList(QFileDialog::getOpenFileName(this, tr("Select a JSON file."), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("JSON files (*.json)")));
}

void MainMenuWidget::handleLevelEditorButton()
{
    mainMenuController->launchLevelEditorOnMainWindow();
}
