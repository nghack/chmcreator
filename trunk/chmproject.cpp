#include "chmproject.h"
#include "global.h"

CHMProject::CHMProject(QString projectFile):QSettings(projectFile,QSettings::IniFormat),hhcFile(0),hhkFile(0)
{
    filePath = projectFile;

    QFileInfo fileInfo(projectFile);
    projectPath = fileInfo.absolutePath();

    projectName = value(PROJECT_EXT_NAME,fileInfo.completeBaseName()).toString();

    hhcFile = new HHCObject(projectName,projectPath+QString("/")+value(PROJECT_CONT_FILE,"index.hhc").toString());
    hhkFile = new HHKObject(projectPath+QString("/")+value(PROJECT_INDEX,QString("index.hhk")).toString());
}
//const QString CHMProject::valueGBK (const QString &key, const QVariant &defaultValue){
//    QByteArray myArray = value(key,defaultValue).toByteArray();
//    QTextCodec *codec=QTextCodec::codecForName("gb2312");
//    return codec->toUnicode(myArray);
//}

CHMProject::~CHMProject()
{
    if(hhcFile!=0){
        delete hhcFile;
    }
    if(hhkFile!=0){
        delete hhkFile;
    }
}
void CHMProject::toProjectFile(){
    QString hhpFilePath = projectPath;
    hhpFilePath.append("/");
    hhpFilePath.append(projectName);
    hhpFilePath.append(".hhp");
    QFile projectFile(hhpFilePath);
    if (!projectFile.open(QFile::WriteOnly)){
        QMessageBox::about(0,filePath,"Open Project File Failure!");
        return;
    }
    QTextStream outputProject(&projectFile);
    outputProject.setCodec(QTextCodec::codecForName("gb2312"));

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
