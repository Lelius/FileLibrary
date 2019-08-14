#ifndef SECONDSEARCHFORM_H
#define SECONDSEARCHFORM_H

#include <QWidget>

namespace Ui {
class SecondSearchForm;
}

class SecondSearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit SecondSearchForm(QWidget *parent = nullptr);
    ~SecondSearchForm();

private:
    Ui::SecondSearchForm *ui;
};

#endif // SECONDSEARCHFORM_H
