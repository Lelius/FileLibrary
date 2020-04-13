#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listform.h"
#include "cardeditform.h"
#include "exitform.h"
#include "newfilelibraryform.h"
#include "cardviewform.h"
#include "workwithdatabase.h"
#include "openfilelibraryform.h"

//TODO резервное копирование (по расписанию?)
//TODO внятная работа с файлами при создании и открытии БД
//TODO группировка карточек, работа с группой
//TODO редактирование и сортировка миниформ

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    listForm = new ListForm();
    cardEditForm = new CardEditForm(this);
    ExitForm *exitForm = new ExitForm(this);
    NewFileLibraryForm *newFileLibraryForm = new NewFileLibraryForm(this);
    cardViewForm = new CardViewForm(this);
    OpenFileLibraryForm *openFileLibraryForm = new OpenFileLibraryForm(this);
    searchForm = new SearchForm(this);

    setActionsEnabled(false);   //выключает часть меню

    //читаем параметры конфигурации из config.txt
    wwcf = new WorkWithConfigFile();
    setProgramConfiguration();

    ui->stackedWidget->insertWidget(0, listForm);
    ui->stackedWidget->insertWidget(1, cardEditForm);
    ui->stackedWidget->insertWidget(2, exitForm);
    ui->stackedWidget->insertWidget(3, newFileLibraryForm);
    ui->stackedWidget->insertWidget(4, cardViewForm);
    ui->stackedWidget->insertWidget(5, openFileLibraryForm);
    ui->stackedWidget->insertWidget(6, searchForm);
    ui->stackedWidget->setCurrentIndex(0);
    previousIndex = 0;

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitChangeStackWidget);
    connect(ui->actionListCard_2, &QAction::triggered, this, &MainWindow::listChangeStackWidget);
    connect(ui->actionListCard_2, &QAction::triggered, listForm, &ListForm::slotListInit);
    connect(ui->actionEditCard, &QAction::triggered, this, &MainWindow::slotActionOnEditCard);
    connect(ui->actionViewCard, &QAction::triggered, this, &MainWindow::slotActionOnViewCard);
    connect(ui->actionCreateNewFileLibrary, &QAction::triggered, this, &MainWindow::newFileLibraryChangeStackWidget);
    connect(exitForm, &ExitForm::noExit, this, &MainWindow::exitBackChangeStackWidget);
    connect(newFileLibraryForm, &NewFileLibraryForm::signalStatusBarOutput, this, &MainWindow::slotStatusBarOutput);
    connect(newFileLibraryForm, &NewFileLibraryForm::signalCardEditChangeStackWidget, this, &MainWindow::cardEditChangeStackWidget);
    connect(newFileLibraryForm, &NewFileLibraryForm::signalSetActionsEnabled, this, &MainWindow::setActionsEnabled);
    connect(ui->actionOpenFileLibrary, &QAction::triggered, this, &MainWindow::openFileLibraryChangeStackWidget);
    connect(ui->actionViewCard, &QAction::triggered, this, &MainWindow::cardViewChangeStackWidget);
    connect(ui->actionNewCard, &QAction::triggered, this, &MainWindow::cardNewChangeStackWidget);
    connect(cardEditForm, &CardEditForm::signalSaveCard, this, &MainWindow::slotCardViewChangeStackWidget);
    connect(openFileLibraryForm, &OpenFileLibraryForm::signalListChangeStackedWidget, this, &MainWindow::listChangeStackWidget);
    connect(openFileLibraryForm, &OpenFileLibraryForm::signalListInit, listForm, &ListForm::slotListInit);
    connect(ui->actionDelCard, &QAction::triggered, listForm, &ListForm::slotDelCard);
    connect(ui->actionCloseFileLibrary, &QAction::triggered, listForm, &ListForm::slotCloseFileLibrary);
    connect(listForm, &ListForm::signalSetActionsEnabled, this, &MainWindow::setActionsEnabled);
    connect(listForm, &ListForm::signalViewSelectedCard, this, &MainWindow::slotViewSelectedCard);
    connect(ui->actionSearch, &QAction::triggered, this, &MainWindow::searchChangeStackWidget);
    connect(searchForm, &SearchForm::signalViewSearchCard, this, &MainWindow::slotViewSelectedCard);
    connect(searchForm, &SearchForm::signalToListCardForEsc, this, &MainWindow::listChangeStackWidget);
    connect(exitForm, &ExitForm::signalCloseProgramm, this, &MainWindow::slotCloseProgramm);
    connect(listForm, &ListForm::signalChangeStackWidget, this, &MainWindow::slotChangeStackWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete cardEditForm;
    delete cardViewForm;
    delete listForm;
    delete searchForm;
    delete wwcf;
}


void MainWindow::setProgramConfiguration()
{
    MainWindow::setGeometry(wwcf->getRectMainWindow());

    if (wwcf->getWindowMaximizedScreenOk() == true && MainWindow::windowState().testFlag(Qt::WindowMaximized) == false)
        MainWindow::setWindowState(MainWindow::windowState() ^ Qt::WindowMaximized);
    if (wwcf->getWindowMaximizedScreenOk() == false && MainWindow::windowState().testFlag(Qt::WindowMaximized) == true)
        MainWindow::setWindowState(MainWindow::windowState() ^ Qt::WindowMaximized);

    if (wwcf->getLastDatabaseName() != "no"){

        WorkWithDatabase wwd;
        wwd.removeDatabase();

        QString pathLastDatabaseName = wwcf->getLastDatabaseName();
        wwd.openDatabase(pathLastDatabaseName);

        delete listForm;
        listForm = new ListForm(this);

        setActionsEnabled(true);
    }

}


void MainWindow::searchChangeStackWidget(){
    previousIndex = ui->stackedWidget->currentIndex();
    slotChangeStackWidget(6);
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


void MainWindow::slotCardViewChangeStackWidget(CardInformation *saveci)
{
    previousIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->removeWidget(cardViewForm);
    delete cardViewForm;
    cardViewForm = new CardViewForm(saveci);
    ui->stackedWidget->insertWidget(4, cardViewForm);
    slotChangeStackWidget(4);
}


void MainWindow::cardEditChangeStackWidget()
{
    previousIndex = ui->stackedWidget->currentIndex();
    slotChangeStackWidget(1);
}


void MainWindow::listChangeStackWidget()
{
    QSqlDatabase db = QSqlDatabase::database("FL");
    if (!db.isOpen()){
        qDebug() << "База данных отсутствует";
        setActionsEnabled(false);
    } else
        setActionsEnabled(true);

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


void MainWindow::cardNewChangeStackWidget()
{
    previousIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->removeWidget(cardEditForm);
    delete cardEditForm;
    cardEditForm = new CardEditForm(this);
    connect(cardEditForm, &CardEditForm::signalSaveCard, this, &MainWindow::slotCardViewChangeStackWidget);
    ui->stackedWidget->insertWidget(1, cardEditForm);
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::openFileLibraryChangeStackWidget()
{
    previousIndex = ui->stackedWidget->currentIndex();
    slotChangeStackWidget(5);
}


void MainWindow::slotViewSelectedCard(CardInformation ci)
{
    previousIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->removeWidget(cardViewForm);
    delete cardViewForm;
    cardViewForm = new CardViewForm(&ci, this);
    ui->stackedWidget->insertWidget(4, cardViewForm);
    ui->stackedWidget->setCurrentIndex(4);

    connect(cardViewForm, &CardViewForm::signalCardViewFormToListForm, this, &MainWindow::listChangeStackWidget);
    connect(cardViewForm, &CardViewForm::signalNextOrPreviousCardViewForm, this, &MainWindow::slotViewSelectedCard,Qt::UniqueConnection);
}


void MainWindow::slotActionOnEditCard()
{
    WorkWithDatabase wwd;

    //listForm
    if (ui->stackedWidget->currentIndex() == 0){

        int inventoryNumber = listForm->getSelectedInventoryNumber();

        previousIndex = ui->stackedWidget->currentIndex();
        ui->stackedWidget->removeWidget(cardEditForm);
        delete cardEditForm;
        CardInformation ci = wwd.searchCard(inventoryNumber);
        cardEditForm = new CardEditForm(&ci, this);
        ui->stackedWidget->insertWidget(1, cardEditForm);
        ui->stackedWidget->setCurrentIndex(1);
        connect(cardEditForm, &CardEditForm::signalSaveCard, this, &MainWindow::slotCardViewChangeStackWidget);
    }

    //cardViewForm
    if (ui->stackedWidget->currentIndex() == 4){
        previousIndex = ui->stackedWidget->currentIndex();
        ui->stackedWidget->removeWidget(cardEditForm);
        delete cardEditForm;
        cardEditForm = new CardEditForm(cardViewForm->getViewci(), this);
        ui->stackedWidget->insertWidget(1, cardEditForm);
        ui->stackedWidget->setCurrentIndex(1);
        connect(cardEditForm, &CardEditForm::signalSaveCard, this, &MainWindow::slotCardViewChangeStackWidget);
    }
}


void MainWindow::slotActionOnViewCard()
{
    WorkWithDatabase wwd;

    //listForm
    if (ui->stackedWidget->currentIndex() == 0){

        int inventoryNumber = listForm->getSelectedInventoryNumber();

        previousIndex = ui->stackedWidget->currentIndex();
        ui->stackedWidget->removeWidget(cardViewForm);
        delete cardViewForm;
        CardInformation ci = wwd.searchCard(inventoryNumber);
        cardViewForm = new CardViewForm(&ci, this);
        ui->stackedWidget->insertWidget(4, cardViewForm);
        ui->stackedWidget->setCurrentIndex(4);
    }
}


void MainWindow::setActionsEnabled(bool flag)
{
    ui->actionCloseFileLibrary->setEnabled(flag);
    ui->actionBackupFileLibrary->setEnabled(flag);
    ui->actionListCard_2->setEnabled(flag);
    ui->actionViewCard->setEnabled(flag);
    ui->actionNewCard->setEnabled(flag);
    ui->actionEditCard->setEnabled(flag);
    ui->actionDelCard->setEnabled(flag);
    ui->actionSearch->setEnabled(flag);
}


void MainWindow::slotCloseProgramm()
{
    close();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    wwcf->setRectMainWindow(MainWindow::geometry());
    wwcf->setWindowMaximizedScreenOk(MainWindow::windowState().testFlag(Qt::WindowMaximized));

    QSqlDatabase db = QSqlDatabase::database("FL");
    if (db.isOpen()){
        wwcf->setLastDatabaseName(db.databaseName());
    }
    else {
        wwcf->setLastDatabaseName("no");
    }

    if (!wwcf->writingConfigFile())
        qDebug() << "Not saving config.txt!";

    event->accept();
}
