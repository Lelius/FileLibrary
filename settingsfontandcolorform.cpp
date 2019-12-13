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
