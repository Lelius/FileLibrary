#ifndef CARDVIEWFORM_H
#define CARDVIEWFORM_H

#include <QWidget>

namespace Ui {
class CardViewForm;
}

class CardViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit CardViewForm(QWidget *parent = nullptr);
    ~CardViewForm();

private:
    Ui::CardViewForm *ui;
};

#endif // CARDVIEWFORM_H
