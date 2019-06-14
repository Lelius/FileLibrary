#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listform.h"
#include "cardeditform.h"
#include "exitform.h"
#include "newfilelibraryform.h"
#include "cardviewform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Делаем окно в два раза меньше разрешения рабочего стола
    QScreen *scr = QGuiApplication::primaryScreen();
    QRect rect = scr->geometry();
    MainWindow::resize(rect.width()/2, rect.height()/2);

    ListForm *listForm = new ListForm(this);
    CardEditForm *cardEditForm = new CardEditForm(this);
    ExitForm *exitForm = new ExitForm(this);
    NewFileLibraryForm *newFileLibraryForm = new NewFileLibraryForm(this);
    CardViewForm *cardViewForm = new CardViewForm(this);

    ui->stackedWidget->insertWidget(0, listForm);
    ui->stackedWidget->insertWidget(1, cardEditForm);
    ui->stackedWidget->insertWidget(2, exitForm);
    ui->stackedWidget->insertWidget(3, newFileLibraryForm);
    ui->stackedWidget->insertWidget(4, cardViewForm);
    ui->stackedWidget->setCurrentIndex(0);
    previousIndex = 0;

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitChangeStackWidget);
    connect(ui->actionListCard_2, &QAction::triggered, this, &MainWindow::listChangeStackWidget);
    connect(ui->actionEditCard, &QAction::triggered, this, &MainWindow::cardEditChangeStackWidget);
    connect(ui->actionCreateNewFileLibrary, &QAction::triggered, this, &MainWindow::newFileLibraryChangeStackWidget);
    connect(exitForm, &ExitForm::noExit, this, &MainWindow::exitBackChangeStackWidget);
    connect(newFileLibraryForm, &NewFileLibraryForm::signalStatusBarOutput, this, &MainWindow::slotStatusBarOutput);
    connect(newFileLibraryForm, &NewFileLibraryForm::signalCardEditChangeStackWidget, this, &MainWindow::cardEditChangeStackWidget);
    connect(ui->actionViewCard, &QAction::triggered, this, &MainWindow::cardViewChangeStackWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotChangeStackWidget(int index)
{
    if (index == -2)
        QApplication::exit();
    ui->stackedWidget->setCurrentIndex(index);

}

void MainWindow::slotStatusBarOutput(QString str, int timeOutput)
{
    ui->statusBar->showMessage(str, timeOutput);
}

void MainWindow::cardEditChangeStackWidget()
{
    previousIndex = ui->stackedWidget->currentIndex();
    slotChangeStackWidget(1);
}

void MainWindow::listChangeStackWidget()
{
    previousIndex = ui->stackedWidget->currentIndex();
    slotChangeStackWidget(0);
}

void MainWindow::exitChangeStackWidget()
{
    previousIndex = ui->stackedWidget->currentIndex();
    slotChangeStackWidget(2);
}

void MainWindow::exitBackChangeStackWidget()
{
    slotChangeStackWidget(previousIndex);
}

void MainWindow::newFileLibraryChangeStackWidget()
{
    previousIndex = ui->stackedWidget->currentIndex();
    slotChangeStackWidget(3);
}

void MainWindow::cardViewChangeStackWidget()
{
    previousIndex = ui->stackedWidget->currentIndex();
    slotChangeStackWidget(4);
}
