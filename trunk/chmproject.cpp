#include "chmproject.h"

CHMProject::CHMProject(QString projectFile):QSettings(projectFile,QSettings::IniFormat),hhcFile(0),hhkFile(0)
{
    filePath = projectFile;

    QFileInfo fileInfo(projectFile);
    projectPath = fileInfo.absolutePath();
    QString temp = projectFile;
    projectName = temp.right(temp.length()-temp.lastIndexOf('/')-1);

    hhcFile = new HHCObject(projectName,projectPath+QString("/")+value("OPTIONS/Contents file",QString("index.hhc")).toString());
    hhkFile = new HHKObject(projectPath+value("OPTIONS/Index file",QString("index.hhk")).toString());
}
CHMProject::~CHMProject()
{
    if(hhcFile!=0){
        delete hhcFile;
    }
    if(hhkFile!=0){
        delete hhkFile;
    }
}
void CHMProject::sync (){
    QSettings::sync();

    QFile projectFile(filePath);
    if (!projectFile.open(QFile::WriteOnly))
        return;
    QTextStream outputProject(&projectFile);
    outputProject.setCodec(QTextCodec::codecForName("UTF-8"));

    QStringList keyList = childGroups();
    foreach(QString key,keyList){
        outputProject <<"[";
        outputProject <<key;
        outputProject <<"]\r\n";
        beginGroup(key);
        QStringList childKeyList = childKeys();
        foreach(QString childKey,childKeyList){
            outputProject <<childKey;
            outputProject <<"=";
            outputProject <<value(childKey).toString();
            outputProject <<"\r\n";
        }
        endGroup();
    }
    outputProject.flush();
    projectFile.close();
}
