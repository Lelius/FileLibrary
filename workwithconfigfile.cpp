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

    //Если есть файл config.txt восстанавливаем из него состояние
    loadFromConfigFileGeometryMainWindow();
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

    if (file.isOpen())
        file.close();
    return true;
}


void WorkWithConfigFile::loadFromConfigFileGeometryMainWindow()
{
    if (!file.exists())
        return;
    if (file.isOpen())
        file.close();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        getFromCofigFileRectMainWindow();
        file.close();
    }
}


void WorkWithConfigFile::getFromCofigFileRectMainWindow()
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
