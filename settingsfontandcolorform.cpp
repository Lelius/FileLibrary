#include "settingsfontandcolorform.h"
#include "ui_settingsfontandcolorform.h"

SettingsFontAndColorForm::SettingsFontAndColorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsFontAndColorForm)
{
    ui->setupUi(this);
    par = parent;
}

SettingsFontAndColorForm::~SettingsFontAndColorForm()
{
    delete ui;
}

QColor SettingsFontAndColorForm::getColorFontButtonMainWindow() const
{
    return colorFontButtonMainWindow;
}

void SettingsFontAndColorForm::setColorFontButtonMainWindow(const QColor &value)
{
    colorFontButtonMainWindow = value;
}

QColor SettingsFontAndColorForm::getColorButtonMainWindow() const
{
    return colorButtonMainWindow;
}

void SettingsFontAndColorForm::setColorButtonMainWindow(const QColor &value)
{
    colorButtonMainWindow = value;
}

QColor SettingsFontAndColorForm::getColorMainWindow() const
{
    return colorMainWindow;
}

void SettingsFontAndColorForm::setColorMainWindow(const QColor &value)
{
    colorMainWindow = value;
}


void SettingsFontAndColorForm::on_pushButtonColorMainWindow_clicked()
{
    setColorPaletteWithRole(QPalette::Window, &colorMainWindow);
}


void SettingsFontAndColorForm::on_pushButtonColorButtonsMainWindow_clicked()
{
    setColorPaletteWithRole(QPalette::Button, &colorButtonMainWindow);
}


void SettingsFontAndColorForm::on_pushButtonColorFontButtonsMainWindow_clicked()
{
    setColorPaletteWithRole(QPalette::ButtonText, &colorFontButtonMainWindow);
}

void SettingsFontAndColorForm::setColorPaletteWithRole(QPalette::ColorRole cr, QColor *c)
{
    *c = QColorDialog::getColor();
    QPalette palette = par->palette();
    palette.setColor(cr, *c);
    par->setPalette(palette);
}
