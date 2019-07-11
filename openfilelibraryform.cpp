#include "openfilelibraryform.h"
#include "ui_openfilelibraryform.h"
#include "workwithdatabase.h"

OpenFileLibraryForm::OpenFileLibraryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenFileLibraryForm)
{
    ui->setupUi(this);

    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::currentPath());

    QStringList stringList;
    fileSystemModel->setNameFilters(stringList << "*.db");
    fileSystemModel->setNameFilterDisables(false);

    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setRootIndex(fileSystemModel->index(QDir::currentPath()));

    QHeaderView *headerOpenFileLibrary = ui->treeView->header();
    headerOpenFileLibrary->setSectionResizeMode(QHeaderView::Stretch);
}

OpenFileLibraryForm::~OpenFileLibraryForm()
{
    delete ui;
}

void OpenFileLibraryForm::on_treeView_activated(const QModelIndex &index)
{
    QFileInfo fileInfo = fileSystemModel->fileInfo(index);
    if (fileInfo.isFile()){
        QString path = fileInfo.filePath();
        WorkWithDatabase wwd;
        wwd.removeDatabase();
        wwd.openDatabase(path);
    }
}
