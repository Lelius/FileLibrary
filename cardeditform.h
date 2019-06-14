#ifndef CARDEDITFORM_H
#define CARDEDITFORM_H

#include <QWidget>
#include "cardinformation.h"

namespace Ui {
class CardEditForm;
}

class CardEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit CardEditForm(QWidget *parent = nullptr);
    ~CardEditForm();

private slots:
    void on_pushButtonSaveCard_clicked();

private:
    Ui::CardEditForm *ui;
    CardInformation *newci;
};

#endif // CARDEDITFORM_H
