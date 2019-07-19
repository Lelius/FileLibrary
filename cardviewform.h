#ifndef CARDVIEWFORM_H
#define CARDVIEWFORM_H

#include <QWidget>

#include "cardinformation.h"

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

private:
    Ui::CardViewForm *ui;
    CardInformation *viewci;
};

#endif // CARDVIEWFORM_H
