#include "newfilelibraryform.h"
#include "ui_newfilelibraryform.h"
#include "workwithdatabase.h"

#include <QTimer>
#include <QDebug>
#include <QMessageBox>

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

    //TODO разобраться с нижней строкой окна NewFileLibraryForm
    if(str != strResult) {

        myMessageBoxOk("Некорректные символы! Использовать можно только буквы и цифры не более двадцати символов!");

    } else if (str.length() >20) {

        myMessageBoxOk("Слишком длинное имя! Использовать можно только буквы и цифры не более двадцати символов!");

    } else {

        nameNewFileLibrary = str + ".db";
        QFile *file = new QFile(nameNewFileLibrary);
        QFileInfo *fileInfo = new QFileInfo(nameNewFileLibrary);

        if ((fileInfo->exists() && fileInfo->isFile())) {

            myMessageBoxOk("Такой файл уже есть!");

        }

        else {
            file->open(QIODevice::WriteOnly);
            file->close();

            WorkWithDatabase wwd;
            if (!wwd.openDatabase(nameNewFileLibrary))
                myMessageBoxOk("Создание: не открылся файл базы данных!");
            if (!wwd.createNewDatabase())
                myMessageBoxOk("Создание: не создалась таблица в базе данных!");

            myMessageBoxOk("Новая картотека " + nameNewFileLibrary + " успешно создана.");

            emit signalCardEditChangeStackWidget();
        }
    }
}


void NewFileLibraryForm::myMessageBoxOk(const QString &str)
{
    QMessageBox::warning(this,"Внимание! ",str , "Понятно.");
}
