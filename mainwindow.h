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
#include "workwithconfigfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalListDelCard();

private slots:
    void slotChangeStackWidget(int index);
    void slotStatusBarOutput(QString str, int timeOutput);
    void slotCardViewChangeStackWidget(CardInformation *saveci);
    void slotViewSelectedCard(CardInformation ci);
    void slotActionOnEditCard();
    void slotActionOnViewCard();
    void slotCloseProgramm();
    void slotDelCard();

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
    void setProgramConfiguration();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    int previousIndex;

    CardEditForm *cardEditForm;
    CardViewForm *cardViewForm;
    ListForm *listForm;
    SearchForm *searchForm;

    WorkWithConfigFile *wwcf;
};

#endif // MAINWINDOW_H
