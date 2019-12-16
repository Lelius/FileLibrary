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

    QColor getColorButtonMainWindow() const;
    void setColorButtonMainWindow(const QColor &value);

    QColor getColorFontButtonMainWindow() const;
    void setColorFontButtonMainWindow(const QColor &value);

private slots:
    void on_pushButtonColorMainWindow_clicked();

    void on_pushButtonColorButtonsMainWindow_clicked();

    void on_pushButtonColorFontButtonsMainWindow_clicked();

    void setColorPaletteWithRole(QPalette::ColorRole, QColor *);

private:
    Ui::SettingsFontAndColorForm *ui;
    QWidget *par;

    QColor colorMainWindow;
    QColor colorButtonMainWindow;
    QColor colorFontButtonMainWindow;
};

#endif // SETTINGSFONTANDCOLORFORM_H
