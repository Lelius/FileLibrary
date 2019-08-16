#ifndef ISSUANCEOFCOPIESMINIFORM_H
#define ISSUANCEOFCOPIESMINIFORM_H

#include <QWidget>
#include <QKeyEvent>

#include "issuanceofcopies.h"

namespace Ui {
class IssuanceOfCopiesMiniForm;
}

class IssuanceOfCopiesMiniForm : public QWidget
{
    Q_OBJECT

public:
    explicit IssuanceOfCopiesMiniForm(QWidget *parent = nullptr);
    ~IssuanceOfCopiesMiniForm();

signals:
    void signalIssuanceOfCopiesMiniFormAdd(IssuanceOfCopies &arg);
    void signalIssuanceOfCopiesMiniFormClose();

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonBack_clicked();
    void keyPressEvent(QKeyEvent *);

private:
    Ui::IssuanceOfCopiesMiniForm *ui;
};

#endif // ISSUANCEOFCOPIESMINIFORM_H
