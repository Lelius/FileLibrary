#ifndef ISSUANCEOFCOPIESMINIFORM_H
#define ISSUANCEOFCOPIESMINIFORM_H

#include <QWidget>

namespace Ui {
class IssuanceOfCopiesMiniForm;
}

class IssuanceOfCopiesMiniForm : public QWidget
{
    Q_OBJECT

public:
    explicit IssuanceOfCopiesMiniForm(QWidget *parent = nullptr);
    ~IssuanceOfCopiesMiniForm();

private:
    Ui::IssuanceOfCopiesMiniForm *ui;
};

#endif // ISSUANCEOFCOPIESMINIFORM_H
