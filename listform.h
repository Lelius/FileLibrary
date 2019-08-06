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

    enum SORT_METHOD {INVENTORY_NUMBER_ASC, INVENTORY_NUMBER_DES,
                      DESIGNATION_ASC, DESIGNATION_DES,
                      NAME_ASC, NAME_DES,
                      DATE_ASC, DATE_DES };

    SORT_METHOD sortMethod;

    void slotListInit();
    void slotDelCard();
    void slotCloseFileLibrary();
    int getSelectedInventoryNumber();
    QVector<CardInformation> sortList(QVector<CardInformation>);
    QVector<CardInformation> sortListByInventoryNumber(QVector<CardInformation>);
    QVector<CardInformation> sortListByDesignation(QVector<CardInformation>);
    QVector<CardInformation> sortListByName(QVector<CardInformation>);
    QVector<CardInformation> sortListByReceiptDate(QVector<CardInformation>);

signals:
    void signalEditCurrentCardInList();
    void signalViewSelectedCard(CardInformation &ci);

private slots:
    void on_tableWidgetList_cellActivated(int row, int column);

private:

    Ui::ListForm *ui;
};

#endif // LISTFORM_H
