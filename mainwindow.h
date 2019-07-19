#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QTableWidget>

#include "cardviewform.h"
#include "cardeditform.h"
#include "cardinformation.h"
#include "listform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotChangeStackWidget(int index);
    void slotStatusBarOutput(QString str, int timeOutput);
    void slotCardViewChangeStackWidget(CardInformation *saveci);
    void slotViewSelectedCard(CardInformation ci);
    void slotActionOnEditCard();

    void cardEditChangeStackWidget();
    void listChangeStackWidget();
    void exitChangeStackWidget();
    void exitBackChangeStackWidget();
    void newFileLibraryChangeStackWidget();
    void cardViewChangeStackWidget();
    void cardNewChangeStackWidget();
    void openFileLibraryChangeStackWidget();

private:
    Ui::MainWindow *ui;
    int previousIndex;

    CardEditForm *cardEditForm;
    CardViewForm *cardViewForm;
    ListForm *listForm;
};

#endif // MAINWINDOW_H
