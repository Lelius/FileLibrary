#include "searchform.h"
#include "ui_searchform.h"

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);

    ui->lineEditSearchText->setText("");
    sci.clear();
    pparent = parent;
}


SearchForm::~SearchForm()
{
    delete ui;
}


void SearchForm::on_pushButtonSearch_clicked()
{
    if (ui->lineEditSearchText->text() == "")
        return;
    QSqlDatabase db = QSqlDatabase::database("FL");
    if (!db.isOpen()){
        qDebug() << "База данных отсутствует";
        return;
    }

    sci.clear();
    searchString = "";

    searchString = ui->lineEditSearchText->text();

    WorkWithDatabase wwd;

    bool numberOk;
    int numb;

    numb = searchString.toInt(&numberOk, 10);
    if (numberOk == true && numb > 0) {
        if (wwd.searchForInventoryNumber(numb) == true)
            sci.append(wwd.searchCard(numb));
    }

    QVector<CardInformation> *aci = new QVector<CardInformation>();
    *aci = wwd.searchCardAll();

    for (CardInformation ci : *aci){
        if (ci.getDesignation().contains(searchString, Qt::CaseInsensitive)){
            sci.append(ci);
        }
        else if (ci.getName().contains(searchString, Qt::CaseInsensitive)){
            sci.append(ci);
        }
        else if (ci.getComment().contains(searchString, Qt::CaseInsensitive)){
            sci.append(ci);
        }
        else if (ci.getReceiptDate().toString("dd.MM.yyyy").contains(searchString, Qt::CaseInsensitive)){
            sci.append(ci);
        }
    }

    delete aci;

    searchWidget = new SecondSearchForm(this);
    searchListForm = new ListForm(sci, this);
    QHBoxLayout *boxLayout = new QHBoxLayout;
    boxLayout->addWidget(searchListForm);
    searchWidget->setLayout(boxLayout);
    searchWidget->setWindowFlag(Qt::Window);
    searchWidget->setWindowModality(Qt::WindowModal);
    searchWidget->setGeometry(pparent->geometry());
    searchWidget->setWindowTitle("Поиск");
    searchWidget->show();

    connect(searchListForm, &ListForm::signalViewSelectedCard, this, &SearchForm::slotCloseSearchWidget, Qt::UniqueConnection);
}


void SearchForm::slotCloseSearchWidget(CardInformation *ci)
{
    searchWidget->close();
    emit signalViewSearchCard(ci);
}

void SearchForm::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        on_pushButtonSearch_clicked();
    if (event->key() == Qt::Key_Escape)
        emit signalToListCardForEsc();
}
