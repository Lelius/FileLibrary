#ifndef COPYACCOUNTINGMINIFORM_H
#define COPYACCOUNTINGMINIFORM_H

#include <QWidget>
#include <QKeyEvent>

#include "copyaccounting.h"

namespace Ui {
class CopyAccountingMiniForm;
}

class CopyAccountingMiniForm : public QWidget
{
    Q_OBJECT

public:
    explicit CopyAccountingMiniForm(QWidget *parent = nullptr);
    ~CopyAccountingMiniForm();

signals:
    void signalCopyAccounteMiniFormClose();
    void signalCopyAccountMiniFormAdd(CopyAccounting &arg);

private slots:
    void on_pushButtonBack_clicked();
    void toShowDateEdit();
    void on_pushButtonReceiptDate_clicked();
    void on_pushButtonDateOfWriteOff_clicked();
    void on_pushButtonReplacementDate_clicked();
    void on_pushButtonAdd_clicked();
    void keyPressEvent(QKeyEvent *);

private:
    Ui::CopyAccountingMiniForm *ui;

    bool viewDateEditReceiptDate;
    bool viewDateEditDateOfWriteOff;
    bool viewDateEditReplacementDate;
};

#endif // COPYACCOUNTINGMINIFORM_H
