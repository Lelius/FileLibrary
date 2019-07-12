#ifndef LISTFORM_H
#define LISTFORM_H

#include <QWidget>
#include <QList>
#include <QVector>

namespace Ui {
class ListForm;
}

class ListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ListForm(QWidget *parent = nullptr);
    ~ListForm();

    void slotListInit();
    void slotDelCard();

private:
    Ui::ListForm *ui;
};

#endif // LISTFORM_H
