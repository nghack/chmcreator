#ifndef QLOCALEMAP_H
#define QLOCALEMAP_H

#include <QObject>
#include <QString>
#include <QMap>

class QLocaleMap : public QObject
{
public:
    QLocaleMap();
    QMap<QString,QString> localeMap;
    const QMap<QString,QString>& getLocale(){return localeMap;}
};

#endif // QLOCALEMAP_H
