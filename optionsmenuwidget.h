#ifndef OPTIONSMENUWIDGET_H
#define OPTIONSMENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStandardPaths>
#include <QFileDialog>

class OptionsMenuController;

enum LastClickedOptionButton {NOBUTTONCLICKED,
                        JUMP,
                        MOVERIGHT,
                        MOVELEFT,
                        RUN,
                        SHOOTFIREBALL };

class OptionsMenuWidget : public QWidget
{
    Q_OBJECT
private:
    OptionsMenuController * optionsMenuController;

    QPushButton defaultButton;
    QPushButton menuButton;
    QPushButton importButton;
    QPushButton exportButton;
    QPushButton keyMoveRightButton;
    QPushButton keyMoveLeftButton;
    QPushButton keyRunButton;
    QPushButton keyJumpButton;
    QPushButton keyShootFireBallButton;


    virtual void keyPressEvent(QKeyEvent * e) override;
public:
    OptionsMenuWidget();
    void setOptionsMenuController(OptionsMenuController * omc){ optionsMenuController = omc; }
    void applyStyleSheet();
    void setTextKeyJumpButton(QString text);
    void setTextKeyRunButton(QString text);
    void setTextKeyMoveRightButton(QString text);
    void setTextKeyMoveLeftButton(QString text);
    void setTextKeyShootFireBallButton(QString text);
    void changeStyleSheetOfTheSelectedButton(QString keyButton);

private slots:
    void handleMenuButton();
    void handleImportButton();
    void handleExportButton();
    void handleMoveRightButton();
    void handleMoveLeftButton();
    void handleJumpButton();
    void handleRunButton();
    void handleShootFireBallButton();
    void handleDefaultButton();
};

#endif // OPTIONSMENUWIDGET_H
