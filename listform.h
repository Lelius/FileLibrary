#ifndef LISTFORM_H
#define LISTFORM_H

#include <QWidget>
#include <QList>
#include <QVector>
#include <QFileInfo>

#include "cardinformation.h"

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
    void slotCloseFileLibrary();

signals:
    void signalEditCurrentCardInList();
    void signalViewSelectedCard(CardInformation &ci);

private slots:
    void on_tableWidgetList_cellActivated(int row, int column);

private:
    Ui::ListForm *ui;
};

#endif // LISTFORM_H
