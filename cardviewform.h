#ifndef CARDVIEWFORM_H
#define CARDVIEWFORM_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QString>

#include "cardinformation.h"
#include "workwithdatabase.h"

namespace Ui {
class CardViewForm;
}

class CardViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit CardViewForm(QWidget *parent = nullptr);
    explicit CardViewForm(CardInformation *ci, QWidget *parent = nullptr);
    ~CardViewForm();

    void cardViewInit();

    CardInformation *getViewci() const;
    void setViewci(CardInformation *value);
    void keyPressEvent(QKeyEvent *);

signals:
    void signalCardViewFormToListForm();
    void signalNextOrPreviousCardViewForm(CardInformation nextorprevci);

private:
    Ui::CardViewForm *ui;
    CardInformation *viewci;
};

#endif // CARDVIEWFORM_H
