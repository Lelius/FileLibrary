#ifndef SETTINGSFONTANDCOLORFORM_H
#define SETTINGSFONTANDCOLORFORM_H

#include <QWidget>
#include <QColorDialog>

namespace Ui {
class SettingsFontAndColorForm;
}

class SettingsFontAndColorForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsFontAndColorForm(QWidget *parent = nullptr);
    ~SettingsFontAndColorForm();

    QColor getColorMainWindow() const;
    void setColorMainWindow(const QColor &value);

private slots:
    void on_pushButtonColorMainWindow_clicked();

signals:
    void changeColorMainWindow(QColor);

private:
    Ui::SettingsFontAndColorForm *ui;

    QColor colorMainWindow;
};

#endif // SETTINGSFONTANDCOLORFORM_H
