#ifndef OPENFILELIBRARYFORM_H
#define OPENFILELIBRARYFORM_H

#include <QWidget>
#include <QFileSystemModel>
#include <QStringList>
#include <QFileInfo>

namespace Ui {
class OpenFileLibraryForm;
}

class OpenFileLibraryForm : public QWidget
{
    Q_OBJECT

public:
    explicit OpenFileLibraryForm(QWidget *parent = nullptr);
    ~OpenFileLibraryForm();

private slots:
    void on_treeView_activated(const QModelIndex &index);

private:
    Ui::OpenFileLibraryForm *ui;
    QFileSystemModel *fileSystemModel;
};

#endif // OPENFILELIBRARYFORM_H
