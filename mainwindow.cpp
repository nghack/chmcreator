#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QSettings settings;
static QString tmpFilePath;

 void spin(QChm* iteration)
 {
     iteration->unzip(tmpFilePath);
 }

MainWindow::MainWindow(QString app,QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow),myapp(app),centerView(new QTabEditor),currentProject(0),property(0)
{
    ui->setupUi(this);
    pro = new QProcess;
    repalceFilesDialog=0;
    createMenus();
    createToolBar();
    createNewWizard();
    setAcceptDrops(true);
    setDockOptions(QMainWindow::ForceTabbedDocks);

    dockIndex = (new QDockWidget(tr("Index"), this));
    dockIndex->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea );
    addDockWidget(Qt::LeftDockWidgetArea, dockIndex);
    dockIndex->setWidget(new QListWidget);

    dockConsole = (new QDockWidget(tr("Console"), this));
    dockConsole->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, dockConsole);
    dockConsole->setWidget(new QTextEdit);

    dockProject = (new QDockWidget(tr("Project"), this));
    dockProject->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea );
    dockProject->setAcceptDrops(true);
    addDockWidget(Qt::LeftDockWidgetArea, dockProject);

    tabifyDockWidget(dockIndex,dockProject);

    QContentsTreeView* viewTree = new QContentsTreeView(this);
    dockProject->setWidget(viewTree);

    //this->connect(viewTree,SIGNAL(clicked(QModelIndex)),this,SLOT(on_action_NewItem_triggered(QModelIndex)));

    connect(pro,SIGNAL(readyReadStandardError()),this,SLOT(console()));
    connect(pro,SIGNAL(readyReadStandardOutput()),this,SLOT(console()));

    setCentralWidget(&mdiArea);

    setWindowState(Qt::WindowMaximized);

    connect((viewTree), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_action_TreeView_Clicked_triggered(const QModelIndex &)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete centerView;
    delete property;
    if(currentProject!=0){
        delete currentProject;
    }
}
QString MainWindow::extractChmFile(QString fileName){

    QChm chm(fileName);
    QString chmProjectName;
    if(chm.open()){
        QString exePath = QCoreApplication::applicationDirPath ();
        QFileInfo fileInfo(fileName);
        QDir qdir;

        qdir.setCurrent(exePath+"/workspace");
        chmProjectName = fileInfo.completeBaseName();
        if(!qdir.exists(chmProjectName)){
            qdir.mkdir(chmProjectName);
        }

        exePath.append("/workspace/");
        exePath.append(chmProjectName);
        tmpFilePath = exePath;
        QVector<QChm*> vector;
        vector.append(&chm);

        // Create a progress dialog.
        QProgressDialog dialog;

        QSize size = QApplication::desktop()->size();
        dialog.setGeometry(QRect((size.width()-500)/2,(size.height()-50)/2,500,50));

        dialog.setWindowTitle(QString("Importing ")+fileName+" as Project...");

        // Create a QFutureWatcher and conncect signals and slots.
        QFutureWatcher<void> futureWatcher;
        QObject::connect(&futureWatcher, SIGNAL(finished()), &dialog, SLOT(reset()));
        QObject::connect(&dialog, SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
        QObject::connect(&chm, SIGNAL(processedFileName(QString)), &dialog, SLOT(setLabelText ( const QString & )));
        QObject::connect(&chm, SIGNAL(valueChanged(int)), &dialog, SLOT(setValue(int)));

        // Start the computation.
        futureWatcher.setFuture(QtConcurrent::map(vector, spin));
        dialog.setRange(0,chm.enumerateFileList().count());
        // Display the dialog and start the event loop.
        dialog.exec();

        futureWatcher.waitForFinished();
        if(futureWatcher.future().isCanceled()){
            return QString::null;
        }
        //chm.unzip(exePath);
    }else{
        return "config/template.hhp";
    }
    chm.close();
    //
    CHMProject settingTemplate(myapp+"/config/template.chmproject");
    CHMProject setting(myapp+"/workspace/"+chmProjectName+"/"+chmProjectName+".chmproject");

    //Project File Sync
    QStringList keyList = settingTemplate.allKeys();
    for(int i=0;i<keyList.count();i++){
        setting.setValue(keyList.at(i),settingTemplate.value(keyList.at(i)));
    }
    setting.setValue(PROJECT_TARGET,chmProjectName+".chm");//path+"/"+
    setting.setValue(PROJECT_CONT_FILE,chm.getHHCFileName());
    setting.setValue(PROJECT_INDEX,chm.getHHKFileName());

    settings.setValue(PROJECT_EXT_NAME,chmProjectName);

    QLocaleMap localMap;
    settings.setValue(PROJECT_LANG,localMap.getLocale().value("Chinese_PRC"));
   /*settings->setValue(PROJECT_EXT_NAME,field("projectName"));

    settings->setValue(PROJECT_BIN_TOC,field("projectBinaryTOC").toString());
    settings->setValue(PROJECT_COMP,((field("projectComplierVersion").toInt()==0)?"1.0":"1.1 or later"));
    settings->setValue(PROJECT_TARGET,field("projectTargetName").toString());
    settings->setValue(PROJECT_CONT_FILE,field("projectContentsFile").toString());//
    settings->setValue(PROJECT_FONT,field("projectFont").toString());
    settings->setValue(PROJECT_DEFAULT_FILE,field("projectDefaultFile").toString());
    settings->setValue(PROJECT_DISPLAY_PROGRESS,"Yes");
    settings->setValue(PROJECT_ENHANCED_DE,field("projectDecompile").toString());
    settings->setValue(PROJECT_LOG_FILE,"log.txt");
    settings->setValue(PROJECT_FLAT,field("projectIncludeFolder").toBool());
    settings->setValue(PROJECT_FULL_SEARCH,field("projectFullTextSearch").toBool());
    settings->setValue(PROJECT_INDEX,field("projectIndexFile").toString());

    QLocaleMap localMap;
    //QString key = languageBox->itemText(field("projectLanuage").toInt());
    settings->setValue(PROJECT_LANG,localMap.getLocale().value("Chinese_PRC"));
    settings->setValue(PROJECT_BIN_INDEX,field("projectBinaryIndex").toBool());
    settings->setValue(PROJECT_TITLE_CHM,field("projectTitle").toString());
    */
    setting.beginGroup(INFOTYPES);
    setting.endGroup();

    setting.sync();
    return myapp+"/workspace/"+chmProjectName+"/"+chmProjectName+".chmproject";
}
void MainWindow::createToolBar()
{
    //Tool Bar
    fileToolBar = addToolBar(tr("Editor"));
    compileToolBar = addToolBar(tr("Compile"));

    //Editor Tool Bar
    newProjectAct = new QAction(QIcon(":/images/new.png"), tr("&New Project"),this);
    connect(newProjectAct, SIGNAL(triggered()), this, SLOT(on_action_New_triggered()));

    openProjectAct = new QAction(QIcon(":/images/open.png"), tr("&Open Project or chm file"),this);
    connect(openProjectAct, SIGNAL(triggered()), this, SLOT(on_action_Open_triggered()));

    saveProjectAct = new QAction(QIcon(":/images/save.png"), tr("&Save File"),this);
    connect(saveProjectAct, SIGNAL(triggered()), this, SLOT(on_action_Save_triggered()));


    fileToolBar->addAction(newProjectAct);
    fileToolBar->addAction(openProjectAct);
    fileToolBar->addAction(saveProjectAct);

    //Editor Tool Bar
    compileProjectAct = new QAction(QIcon(":/images/compile.png"), tr("&Compile Project"),this);
    connect(compileProjectAct, SIGNAL(triggered()), this, SLOT(nextPage()));

    viewProjectAct = new QAction(QIcon(":/images/view.png"), tr("&View Project"),this);
    connect(viewProjectAct, SIGNAL(triggered()), this, SLOT(nextPage()));

    compileToolBar->addAction(compileProjectAct);
    compileToolBar->addAction(viewProjectAct);
}


void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, tr("About chmcreator"),
                       ("The <b>chmcreator</b> is developed by <a href=\"www.ibooks.org.cn\">ibooks</a>.The <b>chmcreator</b> is a excellent chm file editor, which support txt, chm, html format."
                        "欢迎访问<a href =\"www.ibooks.org.cn\">图书之家</a>！"));
}

void MainWindow::on_action_Open_triggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open"),
                                                    tr("chm file or project"),
                                                    tr("HHP Project or chm File (*.chm *.chmproject)"),
                                                    &selectedFilter,
                                                    options);
    if (!fileName.isEmpty()){
        if(fileName.endsWith(".chm",Qt::CaseInsensitive)){
            fileName = extractChmFile(fileName);
            if(fileName==QString::null){
                return;
            }
        }

        loadProject(fileName);
    }
}
void MainWindow::on_action_TreeView_Clicked_triggered(const QModelIndex &index)
{
    QTreeItem *parentItem;
    parentItem = static_cast<QTreeItem*>(index.internalPointer());

    if(index.column()!=0){
        QModifyFileDialog dialog;
        dialog.setModel(currentProject->getProjectPath());
        dialog.exec();
        parentItem->setData(index.column(),dialog.getSelectFile(parentItem->data(index.column()).toString()));
        return;
    }

    QUrl url(currentProject->getProjectPath()+"/"+parentItem->objectUrl().toString());

    if(mdiArea.subWindowList().count()==0){
        mdiArea.addSubWindow(centerView);
        centerView->setWindowState(Qt::WindowMaximized);
    }

    centerView->show();
    centerView->addTab(url.toString());
}
void MainWindow::on_action_NewAccepted_triggered()
{
    QDir dir;
    QString path = myapp+"/workspace/"+wizard.getWizardName();
    dir.mkpath(path);

    const QSettings* newProjectSettings = wizard.getSettings();
    CHMProject setting(path+"/"+wizard.getWizardName()+".chmproject");

    //Project File Sync
    QStringList keyList = newProjectSettings->allKeys();
    foreach(QString key,keyList)
    {
        setting.setValue(key,newProjectSettings->value(key));
    }

    setting.sync();
    //HHC HHK File Sync

    copy(myapp +"/config/index.hhc",path+"/"+ setting.value(PROJECT_CONT_FILE).toString());
    copy(myapp +"/config/index.hhk",path+"/"+setting.value(PROJECT_INDEX).toString());

    //Template File
    copy(myapp +"/config/index.html",path+"/index.html");
    copy(myapp +"/config/intro.html",path+"/intro.html");

    loadProject(setting.getProjectFileName());
}
void MainWindow::copy(QString from,QString to)
{
    QFileInfo fileInfo(to);
    if(!fileInfo.exists()){
        QFile::copy(from,to);
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0,"File already exists","File already exists, if replace?",QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QFile::remove(to);
        QFile::copy(from,to);
    }
}
void MainWindow::createNewWizard(){
    wizard.setWindowModality(Qt::ApplicationModal);
    wizard.setWindowIcon(QIcon(":/images/logo.png"));
    connect(&wizard, SIGNAL(accepted()), this, SLOT(on_action_NewAccepted_triggered()));
}
void MainWindow::on_action_New_triggered()
{
    wizard.restart();
    wizard.show();
}

void MainWindow::on_actionToolBar_triggered()
{
    fileToolBar->setVisible(!fileToolBar->isVisible());
    compileToolBar->setVisible(!compileToolBar->isVisible());
}

void MainWindow::on_actionStatusBar_triggered()
{
    ui->statusBar->setVisible(!ui->statusBar->isVisible());
}

void MainWindow::on_action_Build_triggered()
{
}

void MainWindow::compile()
{
//    QProcess pro;
//    pro.startDetached(QString("hhc ")+currentProject->getProjectFileName());
}
void MainWindow::loadProject(const QString& proFile){
    if(currentProject!=0){
        delete currentProject;
    }
    currentProject = new CHMProject(proFile);

    settings.setValue(PROJECT_PATH,currentProject->getProjectPath());

    QTreeView* treeView = (QTreeView*)dockProject->widget();

    treeView->setModel(currentProject->getHHCObject()->getTreeModel());
}

void MainWindow::on_action_Compile_triggered()
{
    QDir dir;
    dir.setCurrent(myapp);
    ((QTextEdit*)dockConsole->widget())->clear();
    currentProject->toProjectFile();
    QString projectName = currentProject->value(PROJECT_EXT_NAME).toString();

    QString command(myapp);
    command.append("/hhc.exe ");

    QString chmProjectFile = " \"";
    chmProjectFile.append(currentProject->getProjectPath());
    chmProjectFile.append("/");
    chmProjectFile.append(projectName);
    chmProjectFile.append(".hhp\"");

    qDebug()<<chmProjectFile;;
    command.append(chmProjectFile.replace("/","\\"));
    qDebug()<<command;
    pro->start(command);
}

void MainWindow::console()
{
    ((QTextEdit*)dockConsole->widget())->append(pro->readAll());
}

void MainWindow::on_action_Run_triggered()
{
    ((QTextEdit*)dockConsole->widget())->clear();
    QString projectTargetName = currentProject->value(PROJECT_TARGET).toString();
    QFile file(currentProject->getProjectPath()+"/"+ projectTargetName);
    if(!file.exists()){
        return;
    }

    pro->start(QString("hh \"")+currentProject->getProjectPath()+"/"+ projectTargetName);
}

void MainWindow::on_action_Property_triggered()
{
    if(currentProject!=0){
        if(property!=0){
            delete property;
        }
        property = new QProjectPropertiesDialog(currentProject);
        property->setWindowTitle((QString("Properties for %1").arg(currentProject->getProjectName())));
        property->exec();
    }    
}

void MainWindow::on_action_Save_triggered()
{
    centerView->save();\
    if(currentProject!=0)currentProject->getHHCObject()->save();
}

void MainWindow::on_action_NewItem_triggered()
{

}
void MainWindow::saveHHC()
{
    if(currentProject==0)
        return;
    currentProject->getHHCObject()->save();
}
void MainWindow::createMenus()
{
    connect(ui->menu_File, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
    connect(ui->menu_Edit, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
    connect(ui->menuT_ool, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
    connect(ui->menu_Project, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
    connect(ui->menu_View, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
    connect(ui->menu_Test, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
}
void MainWindow::updateMenus()
{
    ui->actionCopy->setEnabled(false);
    ui->actionCo_mpile->setEnabled(currentProject!=0);
    ui->action_Compile->setEnabled(currentProject!=0);
    ui->action_Run->setEnabled(currentProject!=0);
    ui->actionClose_Project->setEnabled(currentProject!=0);

    ui->action_Property->setEnabled(currentProject!=0);
    if(currentProject!=0){
        QFile file(currentProject->getProjectPath()+"/"+ currentProject->value(PROJECT_TARGET).toString());
        ui->action_Run->setEnabled(file.exists());
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionReplace_In_Files_triggered()
{
    if(repalceFilesDialog==0){
        repalceFilesDialog = new QReplaceFilesDialog(myapp,this);
    }
    repalceFilesDialog->setInitualValue(currentProject==0?myapp:currentProject->getProjectPath(),"","","*");
    repalceFilesDialog->exec();
}

void MainWindow::on_actionClose_Project_triggered()
{
    if(currentProject!=0){
        delete currentProject;
        currentProject = 0;
    }
    settings.setValue(PROJECT_PATH,"");
    QTreeView* treeView = (QTreeView*)dockProject->widget();
    treeView->setModel(0);

    if(centerView!=0)centerView->close();
}
