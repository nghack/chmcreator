#include "chmproject.h"
#include "global.h"

CHMProject::CHMProject(QString projectFile):QSettings(projectFile,QSettings::IniFormat),hhcFile(0),hhkFile(0)
{
    filePath = projectFile;

    QFileInfo fileInfo(projectFile);
    projectPath = fileInfo.absolutePath();
    QString temp = projectFile;
    projectName = temp.right(temp.length()-temp.lastIndexOf('/')-1);

    hhcFile = new HHCObject(projectName,projectPath+QString("/")+valueGBK(PROJECT_CONT_FILE,"index.hhc"));
    hhkFile = new HHKObject(projectPath+valueGBK(PROJECT_INDEX,QString("index.hhk")));
}
const QString CHMProject::valueGBK (const QString &key, const QVariant &defaultValue){
    QByteArray myArray = value(key,defaultValue).toByteArray();
    QTextCodec *codec=QTextCodec::codecForName("gb2312");
    return codec->toUnicode(myArray);
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
    //outputProject.setCodec(QTextCodec::codecForName("UTF-8"));

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
