#include "newfilelibraryform.h"
#include "ui_newfilelibraryform.h"

#include <QTimer>

NewFileLibraryForm::NewFileLibraryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewFileLibraryForm)
{
    ui->setupUi(this);
    //а иначе фокус не устанавливается
    QTimer::singleShot(0, ui->lineEditNameFileLibrary, SLOT(setFocus()));
}

NewFileLibraryForm::~NewFileLibraryForm()
{
    delete ui;
}
