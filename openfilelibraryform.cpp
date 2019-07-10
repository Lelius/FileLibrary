#include "openfilelibraryform.h"
#include "ui_openfilelibraryform.h"

OpenFileLibraryForm::OpenFileLibraryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenFileLibraryForm)
{
    ui->setupUi(this);

    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());

    QStringList stringList;
    model->setNameFilters(stringList << "*.db");
    model->setNameFilterDisables(false);

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(QDir::currentPath()));

    QHeaderView *headerOpenFileLibrary = ui->treeView->header();
    headerOpenFileLibrary->setSectionResizeMode(QHeaderView::Stretch);
}

OpenFileLibraryForm::~OpenFileLibraryForm()
{
    delete ui;
}
