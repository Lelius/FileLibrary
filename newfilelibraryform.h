#ifndef NEWFILELIBRARYFORM_H
#define NEWFILELIBRARYFORM_H

#include <QWidget>

namespace Ui {
class NewFileLibraryForm;
}

class NewFileLibraryForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewFileLibraryForm(QWidget *parent = nullptr);
    ~NewFileLibraryForm();

private:
    Ui::NewFileLibraryForm *ui;
};

#endif // NEWFILELIBRARYFORM_H
