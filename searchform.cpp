#include "searchform.h"
#include "ui_searchform.h"

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);

    ui->lineEditSearchText->setText("");
    sci.clear();
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

    QWidget *searchWidget = new QWidget();
    ListForm *searchListForm = new ListForm(sci, this);
    QHBoxLayout *boxLayout = new QHBoxLayout;
    boxLayout->addWidget(searchListForm);
    searchWidget->setLayout(boxLayout);
    searchWidget->setWindowModality(Qt::ApplicationModal);
    searchWidget->show();
}
