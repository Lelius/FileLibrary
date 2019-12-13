#ifndef SETTINGSFONTANDCOLORFORM_H
#define SETTINGSFONTANDCOLORFORM_H

#include <QWidget>

namespace Ui {
class SettingsFontAndColorForm;
}

class SettingsFontAndColorForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsFontAndColorForm(QWidget *parent = nullptr);
    ~SettingsFontAndColorForm();

private:
    Ui::SettingsFontAndColorForm *ui;
};

#endif // SETTINGSFONTANDCOLORFORM_H
