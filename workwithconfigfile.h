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

    void loadFromConfigFileMainWindow();

    void getFromCofigFileMainWindow();
    bool writingConfigFile();

    bool openConfigFileW();

    QString getConfigFileName() const;
    void setConfigFileName(const QString &value);

    QRect getRectMainWindow() const;
    void setRectMainWindow(const QRect &value);

    bool getWindowMaximizedScreenOk() const;
    void setWindowMaximizedScreenOk(bool value);

    QString getLastDatabaseName() const;
    void setLastDatabaseName(const QString &value);

private:

    QScreen *screen;
    QFile file;
    QString configFileName;

    QRect rectMainWindow;
    bool windowMaximizedScreenOk;
    QString lastDatabaseName;
};

#endif // WORKWITHCONFIGFILE_H
