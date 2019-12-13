#include "settingsfontandcolorform.h"
#include "ui_settingsfontandcolorform.h"

SettingsFontAndColorForm::SettingsFontAndColorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsFontAndColorForm)
{
    ui->setupUi(this);
}

SettingsFontAndColorForm::~SettingsFontAndColorForm()
{
    delete ui;
}

void SettingsFontAndColorForm::on_pushButtonColorMainWindow_clicked()
{
    setColorMainWindow(QColorDialog::getColor());
    emit changeColorMainWindow(getColorMainWindow());
}

QColor SettingsFontAndColorForm::getColorMainWindow() const
{
    return colorMainWindow;
}

void SettingsFontAndColorForm::setColorMainWindow(const QColor &value)
{
    colorMainWindow = value;
}
