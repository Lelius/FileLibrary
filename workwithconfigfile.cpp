#include "workwithconfigfile.h"


WorkWithConfigFile::WorkWithConfigFile()
{
    setConfigFileName("config.txt");
    file.setFileName(getConfigFileName());

    //Делаем окно в два раза меньше разрешения рабочего стола
    screen = QGuiApplication::primaryScreen();
    setRectMainWindow(screen->geometry());
    rectMainWindow.setWidth(rectMainWindow.width()/2);
    rectMainWindow.setHeight(rectMainWindow.height()/2);
    windowMaximizedScreenOk = false;

    //Если есть файл config.txt восстанавливаем из него состояние
    loadFromConfigFileMainWindow();
}


bool WorkWithConfigFile::writingConfigFile()
{
    if (!file.remove()){
        qDebug() << "Not removing config.txt";
    }
    if (!openConfigFileW()){
        qDebug() << "Not working openConfigFileRW()!";
        return false;
    }

    QTextStream out(&file);
    QString line = "MainWindow Rect X = " + QString::number(getRectMainWindow().x()) + "\n";
    out << line;
    line = "MainWindow Rect Y = " + QString::number(getRectMainWindow().y()) + "\n";
    out << line;
    line = "MainWindow Rect Width = " + QString::number(getRectMainWindow().width()) + "\n";
    out << line;
    line = "MainWindow Rect Height = " + QString::number(getRectMainWindow().height()) + "\n";
    out << line;
    line = "MainWindow Maximized Screen = ";
    QString lineOk = getWindowMaximizedScreenOk() ? "true\n" : "false\n";
    out << line << lineOk;
    line = "Last DatabaseName = " + getLastDatabaseName();
    out << line;

    if (file.isOpen())
        file.close();
    return true;
}


void WorkWithConfigFile::loadFromConfigFileMainWindow()
{
    if (!file.exists())
        return;
    if (file.isOpen())
        file.close();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        getFromCofigFileMainWindow();
        file.close();
    }
}


void WorkWithConfigFile::getFromCofigFileMainWindow()
{
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        if (line.contains("MainWindow Rect X = ", Qt::CaseInsensitive)){
            QString lineStr = line.remove("MainWindow Rect X = ", Qt::CaseInsensitive);
            bool intOk = false;
            int num = lineStr.toInt(&intOk, 10);
            if (intOk)
                rectMainWindow.setX(num);
        }
        if (line.contains("MainWindow Rect Y = ", Qt::CaseInsensitive)){
            QString lineStr = line.remove("MainWindow Rect Y = ", Qt::CaseInsensitive);
            bool intOk = false;
            int num = lineStr.toInt(&intOk, 10);
            if (intOk)
                rectMainWindow.setY(num);
        }
        if (line.contains("MainWindow Rect Width = ", Qt::CaseInsensitive)){
            QString lineStr = line.remove("MainWindow Rect Width = ", Qt::CaseInsensitive);
            bool intOk = false;
            int num = lineStr.toInt(&intOk, 10);
            if (intOk)
                rectMainWindow.setWidth(num);
        }
        if (line.contains("MainWindow Rect Height = ", Qt::CaseInsensitive)){
            QString lineStr = line.remove("MainWindow Rect Height = ", Qt::CaseInsensitive);
            bool intOk = false;
            int num = lineStr.toInt(&intOk, 10);
            if (intOk)
                rectMainWindow.setHeight(num);
        }

        //full window---------------------------------------------------
        if (line.contains("MainWindow Maximized Screen = ", Qt::CaseInsensitive)){
            QString lineStr = line.remove("MainWindow Maximized Screen = ", Qt::CaseInsensitive);
            if (lineStr == "false")
                setWindowMaximizedScreenOk(false);
            else if (lineStr == "true")
                setWindowMaximizedScreenOk(true);
            else
                setWindowMaximizedScreenOk(false);
        }

        //path to last file database
        if (line.contains("Last DatabaseName = ", Qt::CaseInsensitive)){
            setLastDatabaseName(line.remove("Last DatabaseName = ", Qt::CaseInsensitive));
        }
    }

}


bool WorkWithConfigFile::openConfigFileW()
{
    if (file.isOpen())
        file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    return true;
}


QString WorkWithConfigFile::getConfigFileName() const
{
    return configFileName;
}


void WorkWithConfigFile::setConfigFileName(const QString &value)
{
    configFileName = value;
}


QRect WorkWithConfigFile::getRectMainWindow() const
{
    return rectMainWindow;
}


void WorkWithConfigFile::setRectMainWindow(const QRect &value)
{
    rectMainWindow = value;
}

bool WorkWithConfigFile::getWindowMaximizedScreenOk() const
{
    return windowMaximizedScreenOk;
}

void WorkWithConfigFile::setWindowMaximizedScreenOk(bool value)
{
    windowMaximizedScreenOk = value;
}

QString WorkWithConfigFile::getLastDatabaseName() const
{
    return lastDatabaseName;
}

void WorkWithConfigFile::setLastDatabaseName(const QString &value)
{
    lastDatabaseName = value;
}
