#ifndef EXITFORM_H
#define EXITFORM_H

#include <QWidget>

namespace Ui {
class ExitForm;
}

class ExitForm : public QWidget
{
    Q_OBJECT

public:
    explicit ExitForm(QWidget *parent = nullptr);
    ~ExitForm();

signals:
    void noExit(int index);

private slots:
    void on_pushButtonYes_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::ExitForm *ui;
};

#endif // EXITFORM_H
