#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QSettings settings;
static QString tmpFilePath;

 void spin(QChm* iteration)
 {
     iteration->unzip(tmpFilePath);
 }

MainWindow::MainWindow(QString app,QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow),myapp(app),/*centerView(new QTabEditor),*/currentProject(0),property(0)
{
    ui->setupUi(this);
    setWindowTitle(tr("chmcreator"));

    rsrcPath = ":/images";
    compileProcessDialog = new QProgressDialog(this);
    findDialog = new FindDialog(this);
    pro = new QProcess;
    mdiArea.setViewMode(QMdiArea::TabbedView);

    tabBar = qFindChild<QTabBar*>(&mdiArea);
    QStyleOptionTab opt;
    if (tabBar) {
        opt.init(tabBar);
        opt.shape = tabBar->shape();
        tabBar->setTabsClosable(true);
        tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(tabBar, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(openTabMenu(const QPoint&)));
        connect(tabBar, SIGNAL(tabCloseRequested(int)), &mdiArea,SLOT(closeActiveSubWindow()));
    }

    connect(pro,SIGNAL(readyRead()),this,SLOT(updateCompileText()));
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

    dockProject = (new QDockWidget(tr("Project"), this));
    dockProject->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea );
    dockProject->setAcceptDrops(true);
    addDockWidget(Qt::LeftDockWidgetArea, dockProject);

    tabifyDockWidget(dockIndex,dockProject);

    viewTree = new QContentsTreeView(this);
    dockProject->setWidget(viewTree);

    //this->connect(viewTree,SIGNAL(clicked(QModelIndex)),this,SLOT(on_action_NewItem_triggered(QModelIndex)));


    setCentralWidget(&mdiArea);

    setWindowState(Qt::WindowMaximized);

    rect = geometry();
    setBaseSize(rect.width(),rect.height());
    connect((viewTree), SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_action_TreeView_Clicked_triggered(const QModelIndex &)));
    connect(pro,SIGNAL(finished(int)),this,SLOT(console(int)));

    if(settings.value(WORKSPACE_CURRENT_PROJECT).isValid()){
        QString projectFile = settings.value(WORKSPACE_CURRENT_PROJECT).toString();
        if(QFileInfo(projectFile).exists())
            loadProject(projectFile);
    }
    connect(&mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(subWindowActivated(QMdiSubWindow*)));
    updateMenus();
}
void MainWindow::openTabMenu(const QPoint& pos)
{
    tabMenu->exec(tabBar->mapToGlobal(pos));
}
void MainWindow::subWindowActivated(QMdiSubWindow* subwindow)
{
    QTextEdit* htmlEdit = 0;
    if(0!=subwindow){
        QHTMLEditor* editor = ((QHTMLEditor*)subwindow->widget());
        if(editor==0){
            return;
        }
        encoding->setCurrentIndex(encodeList.indexOf(editor->textCode()->name(),0));
        htmlEdit = editor->htmlEditor();
    }
    if(htmlEdit==0)
        return;
    connect(htmlEdit, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),
            this, SLOT(currentCharFormatChanged(const QTextCharFormat &)));
    connect(htmlEdit, SIGNAL(cursorPositionChanged()),
            this, SLOT(cursorPositionChanged()));
    htmlEdit->setFocus();

    fontChanged(htmlEdit->font());
    colorChanged(htmlEdit->textColor());
    alignmentChanged(htmlEdit->alignment());

    connect(htmlEdit->document(), SIGNAL(modificationChanged(bool)),
            actionSave, SLOT(setEnabled(bool)));
    connect(htmlEdit->document(), SIGNAL(modificationChanged(bool)),
            this, SLOT(setWindowModified(bool)));
    connect(htmlEdit->document(), SIGNAL(undoAvailable(bool)),
            actionUndo, SLOT(setEnabled(bool)));
    connect(htmlEdit->document(), SIGNAL(redoAvailable(bool)),
            actionRedo, SLOT(setEnabled(bool)));

    setWindowModified(htmlEdit->document()->isModified());
    actionSave->setEnabled(htmlEdit->document()->isModified());
    actionUndo->setEnabled(htmlEdit->document()->isUndoAvailable());
    actionRedo->setEnabled(htmlEdit->document()->isRedoAvailable());

    connect(actionUndo, SIGNAL(triggered()), htmlEdit, SLOT(undo()));
    connect(actionRedo, SIGNAL(triggered()), htmlEdit, SLOT(redo()));

    actionCut->setEnabled(false);
    actionCopy->setEnabled(false);

    connect(actionCut, SIGNAL(triggered()), htmlEdit, SLOT(cut()));
    connect(actionCopy, SIGNAL(triggered()), htmlEdit, SLOT(copy()));
    connect(actionPaste, SIGNAL(triggered()), htmlEdit, SLOT(paste()));

    connect(htmlEdit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));
    connect(htmlEdit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
}
MainWindow::~MainWindow()
{
    delete ui;
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
//    fileToolBar = addToolBar(tr("File"));
//    compileToolBar = addToolBar(tr("Compile"));

    //Editor Tool Bar
//    newProjectAct = new QAction(QIcon(":/images/new.png"), tr("&New Project"),this);
//    connect(newProjectAct, SIGNAL(triggered()), this, SLOT(on_action_New_triggered()));
//
//    openProjectAct = new QAction(QIcon(":/images/open.png"), tr("&Open Project or chm file"),this);
//    connect(openProjectAct, SIGNAL(triggered()), this, SLOT(on_action_Open_triggered()));
//
//    saveProjectAct = new QAction(QIcon(":/images/save.png"), tr("&Save File"),this);
//    connect(saveProjectAct, SIGNAL(triggered()), this, SLOT(on_action_Save_triggered()));


//    fileToolBar->addAction(newProjectAct);
//    fileToolBar->addAction(openProjectAct);
//    fileToolBar->addAction(saveProjectAct);

    //Editor Tool Bar
//    compileProjectAct = new QAction(QIcon(":/images/compile.png"), tr("&Compile Project"),this);
//    connect(compileProjectAct, SIGNAL(triggered()), this, SLOT(nextPage()));
//
//    viewProjectAct = new QAction(QIcon(":/images/view.png"), tr("&View Project"),this);
//    connect(viewProjectAct, SIGNAL(triggered()), this, SLOT(nextPage()));
//
//    compileToolBar->addAction(compileProjectAct);
//    compileToolBar->addAction(viewProjectAct);

    //Editor File ToolBar
    editorFileToolBar = addToolBar(tr("Editor"));
    QAction *a;
    a = new QAction(QIcon(":/images/filenew.png"), tr("&New"), this);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(on_action_New_triggered()));
    editorFileToolBar->addAction(a);

    a = new QAction(QIcon(rsrcPath + "/fileopen.png"), tr("&Open..."), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(on_action_Open_triggered()));
    editorFileToolBar->addAction(a);

    actionSave = a = new QAction(QIcon(rsrcPath + "/filesave.png"), tr("&Save"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(on_action_Save_triggered()));
    a->setEnabled(false);
    editorFileToolBar->addAction(a);

    a = actionPrint = new QAction(QIcon(rsrcPath + "/fileprint.png"), tr("&Print..."), this);
    a->setShortcut(QKeySequence::Print);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrint()));
    editorFileToolBar->addAction(a);

    a = new QAction(QIcon(rsrcPath + "/fileprint.png"), tr("Print Preview..."), this);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrintPreview()));

    a = actionToPDF = new QAction(QIcon(rsrcPath + "/pdf.png"), tr("To P&DF..."), this);
    a->setShortcut(Qt::CTRL + Qt::Key_D);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrintPdf()));
    editorFileToolBar->addAction(a);
    ui->menuExport->addAction(a);

    //Editor File ToolBar
    editorEditToolBar = addToolBar(tr("Edit Actions"));

    a = actionUndo = new QAction(QIcon(rsrcPath + "/editundo.png"), tr("&Undo"), this);
    a->setShortcut(QKeySequence::Undo);
    editorEditToolBar->addAction(a);

    a = actionRedo = new QAction(QIcon(rsrcPath + "/editredo.png"), tr("&Redo"), this);
    a->setShortcut(QKeySequence::Redo);
    editorEditToolBar->addAction(a);

    a = actionCut = new QAction(QIcon(rsrcPath + "/editcut.png"), tr("Cu&t"), this);
    a->setShortcut(QKeySequence::Cut);
    editorEditToolBar->addAction(a);
    //menu->addAction(a);
    a = actionCopy = new QAction(QIcon(rsrcPath + "/editcopy.png"), tr("&Copy"), this);
    a->setShortcut(QKeySequence::Copy);
    editorEditToolBar->addAction(a);
    //menu->addAction(a);
    a = actionPaste = new QAction(QIcon(rsrcPath + "/editpaste.png"), tr("&Paste"), this);
    a->setShortcut(QKeySequence::Paste);
    editorEditToolBar->addAction(a);
    //menu->addAction(a);
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());

    //Format Actions ToolBar
    editorFormatToolBar = addToolBar(tr("Format Actions"));

    actionTextBold = new QAction(QIcon(rsrcPath + "/textbold.png"), tr("&Bold"), this);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    editorFormatToolBar->addAction(actionTextBold);
    //menu->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    actionTextItalic = new QAction(QIcon(rsrcPath + "/textitalic.png"), tr("&Italic"), this);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    editorFormatToolBar->addAction(actionTextItalic);
    //menu->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(QIcon(rsrcPath + "/textunder.png"), tr("&Underline"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
    editorFormatToolBar->addAction(actionTextUnderline);
    //menu->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    //menu->addSeparator();

    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

    actionAlignLeft = new QAction(QIcon(rsrcPath + "/textleft.png"), tr("&Left"), grp);
    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignCenter = new QAction(QIcon(rsrcPath + "/textcenter.png"), tr("C&enter"), grp);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignRight = new QAction(QIcon(rsrcPath + "/textright.png"), tr("&Right"), grp);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignJustify = new QAction(QIcon(rsrcPath + "/textjustify.png"), tr("&Justify"), grp);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);

    editorFormatToolBar->addActions(grp->actions());

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(pix, tr("&Color..."), this);
    connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));
    editorFormatToolBar->addAction(actionTextColor);

    addToolBarBreak(Qt::TopToolBarArea);
    editorFormatTwoToolBar = addToolBar(tr("Text Format Actions"));
    editorFormatTwoToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    editorFormatTwoToolBar->setWindowTitle(tr("Format Actions"));


    comboStyle = new QComboBox(editorFormatTwoToolBar);
    editorFormatTwoToolBar->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    connect(comboStyle, SIGNAL(activated(int)),
            this, SLOT(textStyle(int)));

    comboFont = new QFontComboBox(editorFormatTwoToolBar);
    editorFormatTwoToolBar->addWidget(comboFont);
    connect(comboFont, SIGNAL(activated(const QString &)),
            this, SLOT(textFamily(const QString &)));

    comboSize = new QComboBox(editorFormatTwoToolBar);
    comboSize->setObjectName("comboSize");
    editorFormatTwoToolBar->addWidget(comboSize);
    comboSize->setEditable(true);

    QFontDatabase db;
    foreach(int size, db.standardSizes())
        comboSize->addItem(QString::number(size));

    connect(comboSize, SIGNAL(activated(QString)),
            this, SLOT(textSize(const QString &)));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font()
                                                                   .pointSize())));
    encoding = new QComboBox(editorFormatTwoToolBar);
    encoding->setObjectName("encoding");
    editorFormatTwoToolBar->addWidget(encoding);
    comboSize->setEditable(true);

    encodeList = QTextCodec::availableCodecs();
    qSort(encodeList);
    foreach(QByteArray code, encodeList)
    {
        encoding->addItem(QString(code));
    }
    connect(encoding,SIGNAL(currentIndexChanged(QString)),this,SLOT(encodeChange(QString)));
    formatMenu = new QMenu(QLatin1String("Format"), ui->menuBar);

    formatMenu->addAction(actionTextBold);
    formatMenu->addAction(actionTextUnderline);
    formatMenu->addAction(actionTextItalic);
    formatMenu->addSeparator();

    formatMenu->addAction(actionAlignLeft);
    formatMenu->addAction(actionAlignCenter);
    formatMenu->addAction(actionAlignRight);
    formatMenu->addAction(actionAlignJustify);
    formatMenu->addSeparator();

    formatMenu->addAction(actionTextColor);
    ui->menuBar->insertMenu(ui->menu_View->menuAction(),formatMenu);
}
void MainWindow::encodeChange(QString encode)
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    if(0!=subWindow){
        QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
        editor->load(QByteArray(encode.toLatin1().data(),encode.length()));
    }
}
void MainWindow::closeEvent(QCloseEvent *e)
{
    if (maybeSave())
        e->accept();
    else
        e->ignore();
}
bool MainWindow::maybeSave()
{
    QList<QMdiSubWindow*> subWindowList = mdiArea.subWindowList();
    foreach(QMdiSubWindow* list,subWindowList){
        if(!list->close())
            return false;
    }
    return true;
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, tr("About chmcreator"),
                       ("The <b>chmcreator</b> is developed by <a href=\"www.ibooks.org.cn\">ibooks</a>.The <b>chmcreator</b> is a excellent chm file editor, which support txt, chm, html format."
                        "welcome access <a href =\"www.ibooks.org.cn\">www.ibooks.org.cn</a>"));
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

    QUrl url(currentProject->getProjectPath()+"/"+parentItem->objectUrl().toString());

    if(url.toString().endsWith(".chmproject")){
        on_action_Property_triggered();
        return;
    }

    if(index.column()!=0){
        QModifyFileDialog dialog;
        dialog.setModel(currentProject->getProjectPath());
        dialog.exec();
        parentItem->setData(index.column(),dialog.getSelectFile(parentItem->data(index.column()).toString()));
        return;
    }

    QHTMLEditor* htmlEditor = new QHTMLEditor(url.toString());
    mdiArea.addSubWindow(htmlEditor);
    htmlEditor->show();

    encoding->setCurrentIndex(encodeList.indexOf(htmlEditor->textCode()->name(),0));
    //connect(htmlEditor->textEditor(),SIGNAL(undoAvailable(bool)),ui->action_Undo,SLOT(setEnabled(bool)));
    //connect(htmlEditor->textEditor(),SIGNAL(redoAvailable(bool)),ui->action_Redo,SLOT(setEnabled(bool)));
    updateMenus();
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
    reply = QMessageBox::question(0,tr("File already exists"),QString("File %1 already exists, if replace?").arg(to),QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QFile::remove(to);
        QFile::copy(from,to);
    }
}
void MainWindow::copyDir(QString from,QString to)
{
    QFileInfo fileInfo(from);
    QDir dirFrom(from);
    QDir dirTo(to);
    dirFrom.setCurrent(from);
    dirTo.setCurrent(to);
    if(dirTo.exists(fileInfo.fileName())){
       QMessageBox::StandardButton reply;
       reply = QMessageBox::question(0,tr("File already exists"),QString("File %1 already exists, if replace?").arg(fileInfo.fileName()),QMessageBox::Yes | QMessageBox::No);

       if (reply == QMessageBox::No)
       {
           return;
       }
    }
    dirTo.mkdir(fileInfo.fileName());
    copyDirFiles(from,to+"/"+fileInfo.fileName());
}
void MainWindow::copyDirFiles(QString from,QString to)
{
    QDir dirFrom(from);
    QDir dirTo(to);
    dirFrom.setCurrent(from);
    dirTo.setCurrent(to);
    QStringList fileList = dirFrom.entryList();
    foreach(QString fileName,fileList){
        QFileInfo fileInfo(from+"/"+fileName);
        if(fileName.compare(".")==0||fileName.compare("..")==0){
            continue;
        }

        if(fileInfo.isDir()){
            if(!dirTo.exists(fileName)){
                dirTo.mkdir(fileName);
            }
            copyDirFiles(from+"/"+fileName,to+"/"+fileName);
        }else{
            copy(from+"/"+fileName,to+"/"+fileName);
        }
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
void MainWindow::loadDir(const QString& dirName){
    QFileInfo fileInfo(dirName);
    /**HHC File*/
    HHCObject hhcObject(fileInfo.fileName(),dirName);
    hhcObject.saveAs(dirName+"/"+ "index.hhc");

    /**Project File*/
    CHMProject setting(dirName+"/"+fileInfo.fileName()+".chmproject");

    QSettings templateSetting(myapp+"/config/template.chmproject",QSettings::IniFormat);
    QStringList keyList = templateSetting.allKeys();
    foreach(QString key,keyList){
        setting.setValue(key,templateSetting.value(key));
    }

    setting.setValue(PROJECT_EXT_NAME,fileInfo.fileName());
    setting.setValue(PROJECT_TARGET,fileInfo.fileName()+".chm");
    setting.sync();


    /**Default HHC HHK File Sync*/
    copy(myapp +"/config/index.hhk",dirName+"/"+ "/index.hhk");

    loadProject(setting.getProjectFileName());
}
void MainWindow::loadProject(const QString& proFile){
    setCurrentFile(proFile);
    if(currentProject!=0){
        delete currentProject;
    }
    currentProject = new CHMProject(proFile);

    settings.setValue(PROJECT_PATH,currentProject->getProjectPath());
    settings.setValue(WORKSPACE_CURRENT_PROJECT,proFile);
    currentProject->setValue(PROJECT_PATH,currentProject->getProjectPath());

    QTreeView* treeView = (QTreeView*)dockProject->widget();
    treeView->setModel(currentProject->getHHCObject()->getTreeModel());

    QString title = currentProject->getProjectName();
    setWindowTitle(title.append(tr(" - chmcreator")));
}

void MainWindow::on_action_Compile_triggered()
{
    QDir dir;
    dir.setCurrent(myapp);
    currentProject->toProjectFile();
    QString projectName = currentProject->value(PROJECT_EXT_NAME).toString();

    QString command("\"");
    command.append(myapp);
    command.append("/hhc.exe\" ");

    QString chmProjectFile = " \"";
    chmProjectFile.append(currentProject->getProjectPath());
    chmProjectFile.append("/");
    chmProjectFile.append(projectName);
    chmProjectFile.append(".hhp\"");

    qDebug()<<chmProjectFile;;
    command.append(chmProjectFile.replace("/","\\"));
    qDebug()<<command;
    pro->start(command);
    //compileProcessDialog->exec();
}
void MainWindow::updateCompileText(){
    compileProcessDialog->setLabelText(pro->readAllStandardOutput());
}
void MainWindow::console(int value)
{
    on_action_Run_triggered();
    //QMessageBox::about(0,"Compile Finished!","Compile Finished!");
    //((QTextEdit*)dockConsole->widget())->append(pro->readAll());
}

void MainWindow::on_action_Run_triggered()
{
    //((QTextEdit*)dockConsole->widget())->clear();
    QString projectTargetName = currentProject->value(PROJECT_TARGET).toString();
    QFile file(currentProject->getProjectPath()+"/"+ projectTargetName);
    if(!file.exists()){
        return;
    }

    QProcess* process = new QProcess;
    process->start(QString("hh \"")+currentProject->getProjectPath()+"/"+ projectTargetName);
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
    if(currentProject!=0)currentProject->getHHCObject()->save();
    QMdiSubWindow* editor = mdiArea.currentSubWindow();
    if(editor!=0)((QHTMLEditor*)editor->widget())->save();
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
    //connect(ui->menuT_ool, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
    connect(ui->menu_Project, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
    connect(ui->menu_View, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));
    connect(ui->menuExport, SIGNAL(aboutToShow()), this, SLOT(updateMenus()));

    ui->actionShow_File_Column->setChecked(true);

    /*for (int i = 0; i < 5; ++i) {
         recentFileActs[i] = new QAction(this);
         recentFileActs[i]->setVisible(false);
         connect(recentFileActs[i], SIGNAL(triggered()),
                 this, SLOT(openRecentFile()));
         ui->menu_File->addAction(recentFileActs[i]);
     }*/
    tabMenu = new QMenu(QLatin1String(""), tabBar);
    QAction *close_action = tabMenu->addAction(tr("Close"));
    QAction *close_others_action = tabMenu->addAction(tr("Close Others"));
    QAction *close_all_action = tabMenu->addAction(tr("Close All"));

    connect(close_action,SIGNAL(triggered()),&mdiArea,SLOT(closeActiveSubWindow()));
    connect(close_others_action,SIGNAL(triggered()),&mdiArea,SLOT(closeAllSubWindows()));
    connect(close_all_action,SIGNAL(triggered()),&mdiArea,SLOT(closeAllSubWindows()));
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

    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    if(0!=subWindow){
        QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
        if(editor!=0){
            ui->actionSave_As->setEnabled(true);
            ui->action_Save->setEnabled(editor->isChanged());
            ui->action_Undo->setEnabled(editor->isUndoable());
            ui->action_Redo->setEnabled(editor->isRedoable());
            ui->actionCopy->setEnabled(editor->isCopyable());
            ui->action_Cut->setEnabled(editor->isCopyable());
            ui->actionPaste->setEnabled(QApplication::clipboard()->text()!=QString::null);
            ui->actionSelect_All->setEnabled(editor->isEditable());
            actionToPDF->setEnabled(true);
            actionPrint->setEnabled(true);
        }
        return;
    }

    ui->actionSave_As->setEnabled(false);
    ui->action_Save->setEnabled(false);
    ui->action_Undo->setEnabled(false);
    ui->action_Redo->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->action_Cut->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    ui->actionSelect_All->setEnabled(false);
    actionToPDF->setEnabled(false);
    actionPrint->setEnabled(false);
}
QTextEdit* MainWindow::currentHTMLEdit()
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    if(0!=subWindow){
        QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
        if(editor!=0){
            return editor->htmlEditor();
        }
    }
    return 0;
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

    //if(centerView!=0)centerView->close();
    setWindowTitle(tr("chmcreator"));
}
 void MainWindow::setCurrentFile(const QString &fileName)
 {
     QString curFile = fileName;
     QSettings settings("ibooks", "RecentFiles");
     QStringList files = settings.value("recentFileList").toStringList();
     files.removeAll(fileName);
     files.prepend(fileName);
     while (files.size() > 5)
         files.removeLast();

     settings.setValue("recentFileList", files);

     foreach (QWidget *widget, QApplication::topLevelWidgets()) {
         MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
         if (mainWin)
             mainWin->updateRecentFileActions();
     }
 }
void MainWindow::updateRecentFileActions()
{
     /*QSettings settings("ibooks", "RecentFiles");
     QStringList files = settings.value("recentFileList").toStringList();

     int numRecentFiles = qMin(files.size(), (int)5);

     for (int i = 0; i < numRecentFiles; ++i) {
         QString text = files[i];
         recentFileActs[i]->setText(text);
         recentFileActs[i]->setData(files[i]);
         recentFileActs[i]->setVisible(true);
     }
     for (int j = numRecentFiles; j < 5; ++j)
         recentFileActs[j]->setVisible(false);

     //separatorAct->setVisible(numRecentFiles > 0);*/
}

void MainWindow::on_action_Cut_triggered()
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
    editor->textEditor()->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
    editor->textEditor()->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
    editor->textEditor()->paste();
}

void MainWindow::on_action_Undo_triggered()
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
    editor->textEditor()->undo();
}

void MainWindow::on_action_Redo_triggered()
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
    editor->textEditor()->redo();
}

void MainWindow::on_actionDelete_triggered()
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
//    QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
}

void MainWindow::on_actionSelect_All_triggered()
{
    QMdiSubWindow* subWindow = mdiArea.currentSubWindow();
    QHTMLEditor* editor = ((QHTMLEditor*)subWindow->widget());
    editor->textEditor()->selectAll();
}

void MainWindow::on_action_Replace_triggered()
{
    findDialog->exec();
}

void MainWindow::on_actionSuggestion_triggered()
{
    QDesktopServices::openUrl(QUrl("http://www.ibooks.org.cn/index.php/2009-08-17-09-39-53", QUrl::TolerantMode));
}

void MainWindow::on_actionDirectory_As_Project_triggered()
{
    QString dirString = QFileDialog::getExistingDirectory(this,"Select Directory",settings.value("DIR_DEFAULT",".").toString());
    if(dirString==QString::null)
        return;
    settings.setValue("DIR_DEFAULT",dirString);
    QString workSpace = settings.value(WORKSPACE_PATH).toString();
    copyDir(dirString,workSpace);

    QFileInfo fileInfo(dirString);
    loadDir(workSpace+"/"+fileInfo.fileName());
}

void MainWindow::filePrint()
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted) {
        textEdit->print(&printer);
    }
    delete dlg;
#endif
}

void MainWindow::filePrintPreview()
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter *)));
    preview.exec();
#endif
}

void MainWindow::printPreview(QPrinter *printer)
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else
    textEdit->print(printer);
#endif
}


void MainWindow::filePrintPdf()
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
#ifndef QT_NO_PRINTER
//! [0]
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        textEdit->document()->print(&printer);
    }
//! [0]
#endif
}

void MainWindow::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void MainWindow::textStyle(int styleIndex)
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
    QTextCursor cursor = textEdit->textCursor();

    if (styleIndex != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (styleIndex) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListCircle;
                break;
            case 3:
                style = QTextListFormat::ListSquare;
                break;
            case 4:
                style = QTextListFormat::ListDecimal;
                break;
            case 5:
                style = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                style = QTextListFormat::ListUpperAlpha;
                break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);

        cursor.createList(listFmt);

        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void MainWindow::textColor()
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void MainWindow::textAlign(QAction *a)
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}

void MainWindow::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void MainWindow::cursorPositionChanged()
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
    alignmentChanged(textEdit->alignment());
}

void MainWindow::clipboardDataChanged()
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
}

void MainWindow::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    cursor.setCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::fontChanged(const QFont &f)
{
    textEdit = currentHTMLEdit();
    if(textEdit==0){
        return;
    }
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void MainWindow::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}

void MainWindow::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft) {
        actionAlignLeft->setChecked(true);
    } else if (a & Qt::AlignHCenter) {
        actionAlignCenter->setChecked(true);
    } else if (a & Qt::AlignRight) {
        actionAlignRight->setChecked(true);
    } else if (a & Qt::AlignJustify) {
        actionAlignJustify->setChecked(true);
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    if(currentHTMLEdit()==0)
        return;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."),
                                              QString(), tr("HTML-Files (*.htm *.html);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
        return;
    QTextStream ts(&file);
    ts.setCodec(QTextCodec::codecForName("UTF-8"));
    ts << currentHTMLEdit()->document()->toHtml("UTF-8");
    currentHTMLEdit()->document()->setModified(false);
}

void MainWindow::on_actionShow_File_Column_triggered()
{
    if(ui->actionShow_File_Column->isChecked())
    {
        viewTree->showColumn(1);
    }else{
        viewTree->hideColumn(1);
    }
}
