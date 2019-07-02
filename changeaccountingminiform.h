#ifndef CHANGEACCOUNTINGMINIFORM_H
#define CHANGEACCOUNTINGMINIFORM_H

#include <QWidget>

#include "changeaccountingcard.h"

namespace Ui {
class ChangeAccountingMiniForm;
}

class ChangeAccountingMiniForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeAccountingMiniForm(QWidget *parent = nullptr);
    ~ChangeAccountingMiniForm();

signals:
    void signalChangeAccountingMiniFormClose();
    void signalChangeAccountingMiniFormAdd(ChangeAccountingCard &arg);

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonBack_clicked();

private:
    Ui::ChangeAccountingMiniForm *ui;
};

#endif // CHANGEACCOUNTINGMINIFORM_H
