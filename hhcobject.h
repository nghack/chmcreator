#ifndef HHCOBJECT_H
#define HHCOBJECT_H

#include <QObject>
#include <QString>

class HHCObject : public QObject
{
public:
    HHCObject(QString fileName);
private:
    QString fileName;
};

#endif // HHCOBJECT_H
