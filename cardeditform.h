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
    explicit CardEditForm(CardInformation *ci, QWidget *parent = nullptr);
    ~CardEditForm();

    void cardEditInit();

signals:
    void signalSaveCard(CardInformation *ci);

private slots:
    void on_pushButtonSaveCard_clicked();

    void on_pushButtonApplicabilityAdd_clicked();

private:
    Ui::CardEditForm *ui;
    CardInformation *newci;
};

#endif // CARDEDITFORM_H
