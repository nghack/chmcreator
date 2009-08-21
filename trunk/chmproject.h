#ifndef CHMPROJECT_H
#define CHMPROJECT_H

#include <QtGui>
#include "hhcobject.h"
#include "hhkobject.h"

#define COMPILED_FILE QString("OPTIONS/Compiled file")
#define CONTENTS_FILE QString("OPTIONS/Contents file")
#define INDEX_FILE QString("OPTIONS/Index file")
#define LOG_FILE QString("OPTIONS/Error log file")
#define TITLE QString("OPTIONS/Title")

#define INFOTYPES QString("INFOTYPES")

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
private:
    QString filePath;
    QString projectPath;
    QString projectName;
    HHCObject* hhcFile;
    HHKObject* hhkFile;
};

#endif // CHMPROJECT_H
