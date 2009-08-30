#ifndef CHMPROJECT_H
#define CHMPROJECT_H

#include <QtGui>
#include "hhcobject.h"
#include "hhkobject.h"

class CHMProject : public QSettings
{
public:
    CHMProject(QString projectFile);
    ~CHMProject();
    HHCObject* getHHCObject(){return hhcFile;}
    HHKObject* getHHKObject(){return hhkFile;}
    const QString& getProjectFileName(){return filePath;}
    const QString& getProjectPath(){return projectPath;}
    const QString& getProjectName(){return projectName;}
    virtual void sync ();
    const QString valueGBK (const QString &key, const QVariant &defaultValue = QVariant());
private:
    QString filePath;
    QString projectPath;
    QString projectName;
    HHCObject* hhcFile;
    HHKObject* hhkFile;
};

#endif // CHMPROJECT_H
