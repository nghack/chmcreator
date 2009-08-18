#ifndef HHKOBJECT_H
#define HHKOBJECT_H

#include <QObject>
#include <QString>

class HHKObject : public QObject
{
public:
    HHKObject(QString fileName);
private:
    QString fileName;
};

#endif // HHKOBJECT_H
