#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QHBoxLayout>

#include "cardinformation.h"
#include "workwithdatabase.h"
#include "listform.h"

namespace Ui {
class SearchForm;
}

class SearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

private slots:
    void on_pushButtonSearch_clicked();

private:
    Ui::SearchForm *ui;
    QString searchString;
    QVector<CardInformation> sci;
};

#endif // SEARCHFORM_H
