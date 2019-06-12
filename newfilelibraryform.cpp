#include "newfilelibraryform.h"
#include "ui_newfilelibraryform.h"

#include <QTimer>
#include <QDebug>

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

void NewFileLibraryForm::on_lineEditNameFileLibrary_returnPressed()
{
    QString str = ui->lineEditNameFileLibrary->text();
    QString strResult = "";

    for (int i = 0; i < str.length(); i++) {
        if (!(str[i] >= '1' && str[i] <= '9'))
            if(!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
                if(!((str[i] >= "А" && str[i] <= "Я") || (str[i] >= "а" && str[i] <= "я")))
                    break;
        strResult += str[i];
    }

    if(str == strResult)
        qDebug() << strResult;
    else
        qDebug() << "Не корректно!";

    if(str != strResult) {
        emit signalStatusBarOutput("Не корректное имя", 5000);
        ui->lineEditNameFileLibrary->clear();
        ui->lineEditNameFileLibrary->setCursorPosition(0);

    } else if (str.length() >20) {
        emit signalStatusBarOutput("Не более 20 символов", 5000);
        ui->lineEditNameFileLibrary->clear();
        ui->lineEditNameFileLibrary->setCursorPosition(0);

    } else {
        nameNewFileLibrary = str + ".db";
        QFile *file = new QFile(nameNewFileLibrary);
        QFileInfo *fileInfo = new QFileInfo(nameNewFileLibrary);

        if ((fileInfo->exists() && fileInfo->isFile())) {
            emit signalStatusBarOutput("Такой файл уже есть", 5000);
            ui->lineEditNameFileLibrary->clear();
            ui->lineEditNameFileLibrary->setCursorPosition(0);
        }

        else {
            file->open(QIODevice::WriteOnly);
            file->close();

            emit signalStatusBarOutput("Новая картотека создана", 5000);
            ui->lineEditNameFileLibrary->clear();
            ui->lineEditNameFileLibrary->setCursorPosition(0);

            emit signalCardEditChangeStackWidget();
        }
    }
}
