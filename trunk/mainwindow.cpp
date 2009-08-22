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

    createToolBar();
    createNewWizard();

    dockIndex = (new QDockWidget(tr("Index"), this));
    dockIndex->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea );
    addDockWidget(Qt::RightDockWidgetArea, dockIndex);
    dockIndex->setWidget(new QListWidget);

    dockConsole = (new QDockWidget(tr("Console"), this));
    dockConsole->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, dockConsole);
    dockConsole->setWidget(new QTextEdit);

    dockProject = (new QDockWidget(tr("Project"), this));
    dockProject->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea );
    addDockWidget(Qt::LeftDockWidgetArea, dockProject);

    QContentsTreeView* viewTree = new QContentsTreeView(this);
    dockProject->setWidget(viewTree);

    this->connect(viewTree,SIGNAL(clicked(QModelIndex)),this,SLOT(on_action_NewItem_triggered(QModelIndex)));

    connect(pro,SIGNAL(readyReadStandardError()),this,SLOT(console()));
    connect(pro,SIGNAL(readyReadStandardOutput()),this,SLOT(console()));

    setCentralWidget(centerView);
    setWindowState(Qt::WindowMaximized);

    connect(((QTreeView*)dockProject->widget()), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_action_TreeView_Clicked_triggered(const QModelIndex &)));
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
    QString newDirName123;
    if(chm.open()){
        QString exePath = QCoreApplication::applicationDirPath ();
        QFileInfo fileInfo(fileName);
        QDir qdir;

        qdir.setCurrent(exePath+"/workspace");
        newDirName123 = fileInfo.fileName().left(fileInfo.fileName().length()-4);
        if(!qdir.exists(newDirName123)){
            qdir.mkdir(newDirName123);
        }

        exePath.append("/workspace/");
        exePath.append(newDirName123);
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
    CHMProject settingTemplate(myapp+"/config/template.hhp");
    CHMProject setting(myapp+"/workspace/"+newDirName123+"/"+newDirName123+".hhp");

    //Project File Sync
    QStringList keyList = settingTemplate.allKeys();
    for(int i=0;i<keyList.count();i++){
        setting.setValue(keyList.at(i),settingTemplate.value(keyList.at(i)));
    }
    setting.setValue(COMPILED_FILE,newDirName123+".chm");//path+"/"+
    setting.setValue(CONTENTS_FILE,chm.getHHCFileName());
    setting.setValue(INDEX_FILE,chm.getHHKFileName());

    setting.beginGroup(INFOTYPES);
    setting.endGroup();

    setting.sync();

    return myapp+"/workspace/"+newDirName123+"/"+newDirName123+".hhp";
}
void MainWindow::createToolBar()
{
    //Tool Bar
    fileToolBar = addToolBar(tr("Editor"));
    compileToolBar = addToolBar(tr("Compile"));

    //Editor Tool Bar
    newProjectAct = new QAction(QIcon(":/images/new.png"), tr("&Next Page"),this);
    connect(newProjectAct, SIGNAL(triggered()), this, SLOT(on_action_New_triggered()));

    openProjectAct = new QAction(QIcon(":/images/open.png"), tr("&New Letter"),this);
    connect(openProjectAct, SIGNAL(triggered()), this, SLOT(on_action_Open_triggered()));

    saveProjectAct = new QAction(QIcon(":/images/save.png"), tr("&Save"),this);
    connect(saveProjectAct, SIGNAL(triggered()), this, SLOT(on_action_Save_triggered()));


    fileToolBar->addAction(newProjectAct);
    fileToolBar->addAction(openProjectAct);
    fileToolBar->addAction(saveProjectAct);

    //Editor Tool Bar
    compileProjectAct = new QAction(QIcon(":/images/compile.png"), tr("&Next Page"),this);
    connect(compileProjectAct, SIGNAL(triggered()), this, SLOT(nextPage()));

    viewProjectAct = new QAction(QIcon(":/images/view.png"), tr("&Next Page"),this);
    connect(viewProjectAct, SIGNAL(triggered()), this, SLOT(nextPage()));

    compileToolBar->addAction(compileProjectAct);
    compileToolBar->addAction(viewProjectAct);
}


void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, tr("About BookInsight"),
                       ("The <b>BookInsight</b> is a book reader, which support txt, chm, html and pdf."));
}

void MainWindow::on_action_Open_triggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open"),
                                                    tr("chm file or project"),
                                                    tr("HHP Project Files (*.hhp);;CHM File (*.chm)"),
                                                    &selectedFilter,
                                                    options);
    if (!fileName.isEmpty()){
        if(fileName.endsWith(".chm",Qt::CaseInsensitive)){
            fileName = extractChmFile(fileName);
            if(fileName==QString::null){
                return;
            }
        }
        //setCentralWidget(centerView);
        loadProject(fileName);
    }
}
void MainWindow::on_action_TreeView_Clicked_triggered(const QModelIndex &index)
{
    if(index.column()!=0){
        QModifyFileDialog dialog;
        dialog.setModel(currentProject->getProjectPath());
        dialog.exec();
        QMessageBox::about(0,dialog.getSelectFile(QString("not")),dialog.getSelectFile(QString("not")));
        return;
    }
    QTreeItem *parentItem;
    parentItem = static_cast<QTreeItem*>(index.internalPointer());

    qDebug()<<currentProject->getProjectPath()+"/"+parentItem->objectUrl().toString();

    QUrl url(currentProject->getProjectPath()+"/"+parentItem->objectUrl().toString());

    centerView->addTab(url.toString());
}
void MainWindow::on_action_NewAccepted_triggered()
{
    QDir dir;
    QString path = myapp+"/workspace/"+wizard.getWizardName();
    dir.mkpath(path);

    CHMProject settingTemplate("config/template.hhp");
    CHMProject setting(path+"/"+wizard.getWizardName()+".hhp");

    //Project File Sync
    QStringList keyList = settingTemplate.allKeys();
    for(int i=0;i<keyList.count();i++){
        setting.setValue(keyList.at(i),settingTemplate.value(keyList.at(i)));
    }
    setting.setValue(COMPILED_FILE,wizard.getWizardName()+".chm");//path+"/"+
    setting.setValue(CONTENTS_FILE,"index.hhc");
    setting.setValue(INDEX_FILE,"index.hhk");

    setting.beginGroup(INFOTYPES);
    setting.endGroup();

    setting.sync();
    //HHC File Sync
    QFile::copy(myapp +"/config/template.hhc",path+"/index.hhc");

    //HHK File Sync
    QFile::copy(myapp +"/config/template.hhk",path+"/index.hhk");

    //Template File
    QFile::copy(myapp +"/config/index.html",path+"/index.html");
    QFile::copy(myapp +"/config/intro.html",path+"/intro.html");

    loadProject(setting.getProjectFileName());
}
void MainWindow::createNewWizard(){
    wizard.setWindowModality(Qt::ApplicationModal);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/images/logo.png")), QIcon::Normal, QIcon::Off);
    wizard.setWindowIcon(icon);
    connect(&wizard, SIGNAL(accepted()), this, SLOT(on_action_NewAccepted_triggered()));
}
void MainWindow::on_action_New_triggered()
{
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
    QProcess pro;
    pro.startDetached(QString("hhc ")+currentProject->getProjectFileName());
}
void MainWindow::loadProject(const QString& proFile){
    if(currentProject!=0){
        delete currentProject;
    }
    currentProject = new CHMProject(proFile);

    settings.setValue(PROJECT_PATH,currentProject->getProjectPath());
    settings.setValue(PROJECT_NAME,currentProject->getProjectName());

    QTreeView* treeView = (QTreeView*)dockProject->widget();

    treeView->setModel(currentProject->getHHCObject()->getTreeModel());
}

void MainWindow::on_action_Compile_triggered()
{
    QDir dir;
    dir.setCurrent(myapp);
    ((QTextEdit*)dockConsole->widget())->clear();
    QString projectName = currentProject->getProjectName().left(currentProject->getProjectName().indexOf('.'));
    qDebug()<<myapp + QString("/hhc ")+"workspace/"+projectName+"/"+projectName+".hhp";
    pro->start(myapp + QString("/hhc ")+"workspace/"+projectName+"/"+projectName+".hhp");
}

void MainWindow::console()
{
    ((QTextEdit*)dockConsole->widget())->append(pro->readAll());
}

void MainWindow::on_action_Run_triggered()
{
    ((QTextEdit*)dockConsole->widget())->clear();
    QString projectName = currentProject->getProjectName().left(currentProject->getProjectName().indexOf('.'));
    QFile file(currentProject->getProjectPath()+"/"+projectName+".chm");
    qDebug()<<currentProject->getProjectPath()+"/"+projectName+".chm";
    if(!file.exists()){
        return;
    }

    pro->start(QString("hh ")+currentProject->getProjectPath()+"/"+projectName+".chm");
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
