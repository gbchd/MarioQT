#include "mainmenuwidget.h"

#include "mainmenucontroller.h"

MainMenuWidget::MainMenuWidget()
{
    setFixedSize(500, 500);
    QVBoxLayout * layout = new QVBoxLayout(this);
    QHBoxLayout * hlayout = new QHBoxLayout();
    optionsButton.setText("OPTIONS");
    playButton.setText("PLAY");
    levelEditorButton.setText("MAP EDITOR");
    QLabel * label = new QLabel;
    label->setPixmap(QPixmap(":/resources/graphics/welcome.png").scaled(500, 400, Qt::KeepAspectRatio));

    //listWidget style
    applyStyleSheet();

    //Add element in layout
    layout->addWidget(label);
    layout->addWidget(&listWidget);
    layout->addWidget(&playButton);
    layout->addLayout(hlayout);
    hlayout->addWidget(&levelEditorButton);
    hlayout->addWidget(&optionsButton);

    //Connect the buttons to their slots
    connect(&playButton, SIGNAL (clicked()), this, SLOT (handlePlayButton()));
    connect(&optionsButton, SIGNAL (clicked()), this, SLOT (handleOptionsButton()));
}

void MainMenuWidget::applyStyleSheet()
{
    listWidget.setStyleSheet("background-color: black;"
                              "color: white;"
                              "font-size: 20px;"
                              "font-weight : bold;");

     playButton.setStyleSheet("background-color: #BE2801;"
                               "color: white;"
                               "font-size: 20px;"
                               "font-weight : bold;");

     optionsButton.setStyleSheet("background-color: #BE2801;"
                               "color: white;"
                               "font-size: 20px;"
                               "font-weight : bold;");

     levelEditorButton.setStyleSheet("background-color: #BE2801;"
                               "color: white;"
                               "font-size: 20px;"
                               "font-weight : bold;");
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

}

void MainMenuWidget::handleLevelEditorButton()
{

}
