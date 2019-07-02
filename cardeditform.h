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

    void slotApplicabilityMiniFormClose();
    void slotApplicabilityMiniFormAdd(ApplicabilityCard &a);

    void slotChangeAccountingMiniFormAdd(ChangeAccountingCard &arg);
    void slotChangeAccountingMiniFormClose();

    void on_lineEditInventoryNumber_textChanged(const QString &arg1);

    void on_dateEditReceiptDate_dateChanged(const QDate &date);

    void on_lineEditDesignation_textChanged(const QString &arg1);

    void on_textEditName_textChanged();

    void on_textEditComment_textChanged();

    void on_spinBoxA1_valueChanged(int arg1);

    void on_spinBoxA2_valueChanged(int arg1);

    void on_spinBoxA3_valueChanged(int arg1);

    void on_spinBoxA4_valueChanged(int arg1);

    void on_pushButtonChangeAccountingAdd_clicked();

private:
    Ui::CardEditForm *ui;
    CardInformation *newci;
    QWidget *newWindow;
};

#endif // CARDEDITFORM_H
