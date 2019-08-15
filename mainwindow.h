#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QTableWidget>

#include "cardviewform.h"
#include "cardeditform.h"
#include "cardinformation.h"
#include "listform.h"
#include "searchform.h"

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
    void slotActionOnViewCard();

    void cardEditChangeStackWidget();
    void listChangeStackWidget();
    void exitChangeStackWidget();
    void exitBackChangeStackWidget();
    void newFileLibraryChangeStackWidget();
    void cardViewChangeStackWidget();
    void cardNewChangeStackWidget();
    void openFileLibraryChangeStackWidget();
    void searchChangeStackWidget();
    void setActionsEnabled(bool);
    void setActionsCardsEnabled(bool);

private:
    Ui::MainWindow *ui;
    int previousIndex;

    CardEditForm *cardEditForm;
    CardViewForm *cardViewForm;
    ListForm *listForm;
    SearchForm *searchForm;
};

#endif // MAINWINDOW_H
