#ifndef LISTFORM_H
#define LISTFORM_H

#include <QWidget>

namespace Ui {
class ListForm;
}

class ListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ListForm(QWidget *parent = nullptr);
    ~ListForm();

private:
    Ui::ListForm *ui;
};

#endif // LISTFORM_H
