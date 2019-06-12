#ifndef CARDEDITFORM_H
#define CARDEDITFORM_H

#include <QWidget>

namespace Ui {
class CardEditForm;
}

class CardEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit CardEditForm(QWidget *parent = nullptr);
    ~CardEditForm();

private:
    Ui::CardEditForm *ui;
};

#endif // CARDEDITFORM_H
