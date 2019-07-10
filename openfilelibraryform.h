#ifndef OPENFILELIBRARYFORM_H
#define OPENFILELIBRARYFORM_H

#include <QWidget>
#include <QFileSystemModel>
#include <QStringList>

namespace Ui {
class OpenFileLibraryForm;
}

class OpenFileLibraryForm : public QWidget
{
    Q_OBJECT

public:
    explicit OpenFileLibraryForm(QWidget *parent = nullptr);
    ~OpenFileLibraryForm();

private:
    Ui::OpenFileLibraryForm *ui;
};

#endif // OPENFILELIBRARYFORM_H
