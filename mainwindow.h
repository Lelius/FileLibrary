#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>

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

    void cardEditChangeStackWidget();
    void listChangeStackWidget();
    void exitChangeStackWidget();
    void exitBackChangeStackWidget();
    void newFileLibraryChangeStackWidget();

private:
    Ui::MainWindow *ui;
    int previousIndex;
};

#endif // MAINWINDOW_H
