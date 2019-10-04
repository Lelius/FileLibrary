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

    int getOldInventoryNumber() const;
    void setOldInventoryNumber(int value);

signals:
    void signalSaveCard(CardInformation *ci);

private slots:
    void on_pushButtonSaveCard_clicked();
    void on_pushButtonApplicabilityAdd_clicked();

    void slotApplicabilityMiniFormClose();
    void slotApplicabilityMiniFormAdd(ApplicabilityCard &a);

    void slotChangeAccountingMiniFormAdd(ChangeAccountingCard &arg);
    void slotChangeAccountingMiniFormClose();

    void slotCopyAccountingMiniFormAdd(CopyAccounting &arg);
    void slotCopyAccountingMiniFormClose();

    void slotIssuanceOfCopiesMiniFormAdd(IssuanceOfCopies &arg);
    void slotIssuanceOfCopiesMiniFormClose();

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

    void on_pushButtonCopyAccountingAdd_clicked();

    void on_pushButtonIssuanceOfCopiesAdd_clicked();

    void on_pushButtonApplicabilityDel_clicked();

    void on_pushButtonChangeAccountingDel_clicked();

    void on_pushButtonCopyAccountingDel_clicked();

    void on_pushButtonIssuanceOfCopiesDel_clicked();

private:
    Ui::CardEditForm *ui;
    CardInformation *newci;
    QWidget *newWindow;
    int oldInventoryNumber;
};

#endif // CARDEDITFORM_H
