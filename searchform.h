#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QRect>

#include "cardinformation.h"
#include "workwithdatabase.h"
#include "listform.h"
#include "secondsearchform.h"

namespace Ui {
class SearchForm;
}

class SearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

signals:
    void signalViewSearchCard(CardInformation *);
    void signalToListCardForEsc();

private slots:
    void on_pushButtonSearch_clicked();
    void slotCloseSearchWidget(CardInformation *);

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::SearchForm *ui;
    QString searchString;
    QVector<CardInformation> sci;
    SecondSearchForm *searchWidget;
    ListForm *searchListForm;
    QWidget *pparent;
};

#endif // SEARCHFORM_H
