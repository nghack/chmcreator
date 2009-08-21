#include "chmproject.h"

CHMProject::CHMProject(QString projectFile):QSettings(projectFile,QSettings::IniFormat),hhcFile(0),hhkFile(0)
{
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

    QFile file(filePath);
    file.open(QFile::ReadWrite);

    QTextStream stream(&file);
    QString content = stream.readAll();
    content.replace("%20"," ");
    file.close();

    QFile file2(filePath);
    if (!file2.open(QFile::WriteOnly))
        return;
    QTextStream ts(&file2);
    ts.setCodec(QTextCodec::codecForName("UTF-8"));
    ts <<content;
}
