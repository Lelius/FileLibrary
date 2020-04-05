#ifndef NEWFILELIBRARYFORM_H
#define NEWFILELIBRARYFORM_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>

namespace Ui {
class NewFileLibraryForm;
}

class NewFileLibraryForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewFileLibraryForm(QWidget *parent = nullptr);
    ~NewFileLibraryForm();

signals:
    void signalStatusBarOutput(QString str, int timeOutput); //после перехода на QMessageBox в этой форме не используется
    void signalCardEditChangeStackWidget();
    void signalSetActionsEnabled(bool);

private slots:
    void on_lineEditNameFileLibrary_returnPressed();

    void myMessageBoxOk(const QString &);

private:
    Ui::NewFileLibraryForm *ui;
    QString nameNewFileLibrary;
};

#endif // NEWFILELIBRARYFORM_H
