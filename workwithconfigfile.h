#ifndef WORKWITHCONFIGFILE_H
#define WORKWITHCONFIGFILE_H

#include <QString>
#include <QScreen>
#include <QFile>
#include <QGuiApplication>
#include <QMainWindow>
#include <QTextStream>
#include <QDebug>


class WorkWithConfigFile
{
public:

    WorkWithConfigFile();

    void loadFromConfigFileGeometryMainWindow();

    void getFromCofigFileRectMainWindow();
    bool writingConfigFile();

    bool openConfigFileW();

    QString getConfigFileName() const;
    void setConfigFileName(const QString &value);

    QRect getRectMainWindow() const;
    void setRectMainWindow(const QRect &value);

private:

    QScreen *screen;
    QFile file;
    QString configFileName;

    QRect rectMainWindow;
};

#endif // WORKWITHCONFIGFILE_H
