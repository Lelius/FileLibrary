#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>

#include "cardviewform.h"
#include "cardeditform.h"
#include "cardinformation.h"

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
};

#endif // MAINWINDOW_H
