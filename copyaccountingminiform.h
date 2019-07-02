#ifndef COPYACCOUNTINGMINIFORM_H
#define COPYACCOUNTINGMINIFORM_H

#include <QWidget>

namespace Ui {
class CopyAccountingMiniForm;
}

class CopyAccountingMiniForm : public QWidget
{
    Q_OBJECT

public:
    explicit CopyAccountingMiniForm(QWidget *parent = nullptr);
    ~CopyAccountingMiniForm();

private:
    Ui::CopyAccountingMiniForm *ui;
};

#endif // COPYACCOUNTINGMINIFORM_H
