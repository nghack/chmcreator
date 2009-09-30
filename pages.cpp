#include <QtGui>

#include "pages.h"

extern QSettings settings;

ButtonsPage::ButtonsPage(QSettings* setting,QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QGroupBox *configGroup = new QGroupBox(tr("Button Types"));
    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addWidget(new QCheckBox("Hide/Show"),0,0);
    groupLayout->addWidget(new QCheckBox("Back"),1,0);
    groupLayout->addWidget(new QCheckBox("Forward"),2,0);
    groupLayout->addWidget(new QCheckBox("Stop"),3,0);
    groupLayout->addWidget(new QCheckBox("Refresh"),4,0);
    groupLayout->addWidget(new QCheckBox("Home"),5,0);
    groupLayout->addWidget(new QCheckBox("Options"),6,0);
    groupLayout->addWidget(new QCheckBox("Print"),7,0);
    groupLayout->addWidget(new QCheckBox("Locate"),8,0);
    groupLayout->addWidget(new QCheckBox("Jump1"),9,0);
    groupLayout->addWidget(new QCheckBox("Jump2"),10,0);
    configGroup->setLayout(groupLayout);
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}
void ButtonsPage::save(){

}

void ComplierPage::save(){
    settings->setValue(PROJECT_COMP,compatibiBox->currentText());
    settings->setValue(PROJECT_FLAT,dontIncludeFolder->isChecked());
    settings->setValue(PROJECT_ENHANCED_DE,enhancedDecomp->isChecked());
    settings->setValue(PROJECT_FULL_SEARCH,fullSearchSpt->isChecked());
    settings->setValue(PROJECT_BIN_INDEX,binaryIndex->isChecked());
    settings->setValue(PROJECT_BIN_TOC,binaryToc->isChecked());
}
ComplierPage::ComplierPage(QSettings* setting,QWidget *parent)
    : QWidget(parent)
{
    settings = setting;
    QHBoxLayout *compilerLayout = new QHBoxLayout;
    compilerLayout->addWidget(new QLabel(tr("Compatibility:")));

    compatibiBox = new QComboBox;
    compatibiBox->addItem("1.0");
    compatibiBox->addItem(tr("1.1 or Later"));//setting->value(PROJECT_DEFAULT_FILE,tr("index.html")).toString()
    compilerLayout->addWidget(compatibiBox);
    if(setting->value(PROJECT_COMP,tr("1.0")).toString().compare("1.0")==0){
        compatibiBox->setCurrentIndex(0);
    }else{
        compatibiBox->setCurrentIndex(1);
    }
    compilerLayout->addStretch(0);

    QVBoxLayout *mainComplierLayout = new QVBoxLayout;

    dontIncludeFolder = new QCheckBox(tr("Don't Include Folder in Compiled File."));
    enhancedDecomp = new QCheckBox(tr("Support Enhanced Decompliation."));
    fullSearchSpt = new QCheckBox(tr("Full Text Search Support."));
    binaryIndex = new QCheckBox(tr("Create Binary Index."));
    binaryToc = new QCheckBox(tr("Create Binary TOC(Large TOC File.)"));

    dontIncludeFolder->setChecked(setting->value(PROJECT_FLAT,false).toBool());
    enhancedDecomp->setChecked(setting->value(PROJECT_ENHANCED_DE,false).toBool());
    fullSearchSpt->setChecked(setting->value(PROJECT_FULL_SEARCH,false).toBool());
    binaryIndex->setChecked(setting->value(PROJECT_BIN_INDEX,false).toBool());
    binaryToc->setChecked(setting->value(PROJECT_BIN_TOC,false).toBool());

    mainComplierLayout->addLayout(compilerLayout);
    mainComplierLayout->addWidget(dontIncludeFolder);
    mainComplierLayout->addWidget(enhancedDecomp);
    mainComplierLayout->addWidget(fullSearchSpt);
    mainComplierLayout->addWidget(binaryIndex);
    mainComplierLayout->addWidget(binaryToc);
    mainComplierLayout->addStretch(1);

    setLayout(mainComplierLayout);
}

WindowPage::WindowPage(QSettings* setting,QWidget *parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel(this);
    label->setText("<b>Window Style Define</b><br/>Window Style");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(label);
    layout->addStretch(1);

    setLayout(layout);
}
void WindowPage::save(){

}


GeneralTab::GeneralTab(QSettings* setting,QWidget *parent)
    : QWidget(parent)
{
    settings = setting;
    QLabel *fileNameLabel = new QLabel(tr("Title:"));
    fileNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_TITLE_CHM).toString());

    QLabel *targetLabel = new QLabel(tr("Compiled File:"));
    targetNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_TARGET).toString());

    QLabel *contentsLabel = new QLabel(tr("Contents File:"));
    contentsNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_CONT_FILE).toString());

    QLabel *indexLabel = new QLabel(tr("Indexes File:"));
    indexNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_INDEX).toString());

    QLabel *logLabel = new QLabel(tr("Log File:"));
    logNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_LOG_FILE).toString());


    QLabel *pathLabel = new QLabel(tr("Default File:"));
    QHBoxLayout *hlayout = new QHBoxLayout;

    //
    pathValueLabel = new QComboBox();
    pathValueLabel->setEditable(true);

    hlayout->addWidget(pathValueLabel);
    pathValueLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    butn = new QPushButton("Browser...",this);
    connect(butn,SIGNAL(clicked()),this,SLOT(setDefaultFile()));
    hlayout->addWidget(butn);


    QDir directory = QDir(setting->value(PROJECT_PATH).toString());
    directory.setCurrent(setting->value(PROJECT_PATH).toString());
    QStringList fileList = directory.entryList(QDir::Files);
    if(!fileList.contains(setting->value(PROJECT_DEFAULT_FILE).toString())){
        fileList.insert(0,setting->value(PROJECT_DEFAULT_FILE).toString());
    }

    pathValueLabel->addItems(fileList);
    pathValueLabel->setCurrentIndex(fileList.indexOf(setting->value(PROJECT_DEFAULT_FILE).toString()));

    QGroupBox* groupBox = new QGroupBox;
    groupBox->setTitle(tr("International Setting"));

    QGridLayout *groupLayout = new QGridLayout;

    QLabel *languageLabel = new QLabel(tr("Language:"));
    languageBox = new QComboBox;
    QLocaleMap localeMap;
    QList<QString> tempContry = localeMap.getLocale().keys();
    foreach(QString contry,tempContry){
        languageBox->addItem(contry);//PROJECT_LANG
    }

    languageBox->setCurrentIndex(localeMap.getLocale().values().indexOf(setting->value(PROJECT_LANG).toString()));

    QLabel *fontLabel = new QLabel(tr("Font:"));
    fontBox = new QLineEdit;
    fontBox->setText(setting->value(PROJECT_FONT).toString());
    QPushButton* fontButton = new QPushButton(tr("Browser..."));

    connect(fontButton,SIGNAL(clicked()),this,SLOT(setFont()));

    groupLayout->addWidget(languageLabel, 0, 0);
    groupLayout->addWidget(languageBox, 1, 0,1, 2);
    //groupLayout->addWidget(languageButton, 1, 1);

    groupLayout->addWidget(fontLabel, 2, 0);
    groupLayout->addWidget(fontBox, 3, 0);
    groupLayout->addWidget(fontButton, 3, 1);

    groupBox->setLayout(groupLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(fileNameEdit);
    mainLayout->addWidget(targetLabel);
    mainLayout->addWidget(targetNameEdit);
    mainLayout->addWidget(contentsLabel);
    mainLayout->addWidget(contentsNameEdit);
    mainLayout->addWidget(indexLabel);
    mainLayout->addWidget(indexNameEdit);
    mainLayout->addWidget(logLabel);
    mainLayout->addWidget(logNameEdit);
    mainLayout->addWidget(pathLabel);
    mainLayout->addLayout(hlayout);
    mainLayout->addWidget(groupBox);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void GeneralTab::setDefaultFile(){
    QModifyFileDialog dialog;
    dialog.setModel(settings->value(PROJECT_PATH).toString());
    dialog.exec();
    QString file = dialog.getSelectFile(pathValueLabel->currentText());
    if(file!=pathValueLabel->currentText()){
        pathValueLabel->insertItem(0,file);
    }
    pathValueLabel->setCurrentIndex(0);
    return;
}
void GeneralTab::setFont(){
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont(fontBox->text()), this);
    if (ok) {
        fontBox->setText(font.key());
    }
}
void GeneralTab::save(){
    settings->setValue(PROJECT_TITLE_CHM,fileNameEdit->text());
    settings->setValue(PROJECT_TARGET,targetNameEdit->text());
    settings->setValue(PROJECT_CONT_FILE,contentsNameEdit->text());//
    settings->setValue(PROJECT_INDEX,indexNameEdit->text());
    settings->setValue(PROJECT_LOG_FILE,logNameEdit->text());
    settings->setValue(PROJECT_DEFAULT_FILE,pathValueLabel->currentText());

    QLocaleMap localMap;
    //QString key = languageBox->itemText(field("projectLanuage").toInt());
    settings->setValue(PROJECT_LANG,localMap.getLocale().value(languageBox->currentText()));
    settings->setValue(PROJECT_FONT,fontBox->text());

}
void PositionPage::save(){

}
PositionPage::PositionPage(QSettings* setting, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QGroupBox *configGroup = new QGroupBox(tr("Window Size And Positison"));
    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addWidget(new QLabel("Left:"),0,0);
    groupLayout->addWidget(new QLineEdit(""),0,1);
    groupLayout->addWidget(new QLabel("Top:"),1,0);
    groupLayout->addWidget(new QLineEdit(""),1,1);
    groupLayout->addWidget(new QLabel("Width:"),2,0);
    groupLayout->addWidget(new QLineEdit(""),2,1);
    groupLayout->addWidget(new QLabel("Height:"),3,0);
    groupLayout->addWidget(new QLineEdit(""),3,1);

    configGroup->setLayout(groupLayout);
    mainLayout->addWidget(configGroup);
    mainLayout->addWidget(new QCheckBox("Save User Defined Window Position After Firist Use."));
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}
//! [7]
void NavPage::save(){

}
//! [8]
NavPage::NavPage(QSettings* setting,QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QCheckBox("Window with Navgition Panel,Topic and Buttons."));
    mainLayout->addWidget(new QLabel("Navgition Panel"));
    mainLayout->addWidget(new QSpinBox);

    QGroupBox *configGroup = new QGroupBox(tr("Propertities"));
    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addWidget(new QCheckBox("Open With Navgation Close."),0,0);
    groupLayout->addWidget(new QCheckBox("Auto Sync."),1,0);
    groupLayout->addWidget(new QCheckBox("Automatically Show/Hide Navgation."),2,0);
    configGroup->setLayout(groupLayout);
    mainLayout->addWidget(configGroup);

    QGroupBox *tabsGroup = new QGroupBox(tr("Tabs"));
    QGridLayout *tabsLayout = new QGridLayout;
    tabsLayout->addWidget(new QLabel("Default Tab:"),0,0);
    tabsLayout->addWidget(new QComboBox,1,0);
    tabsLayout->addWidget(new QCheckBox("Search tab."),2,0);
    tabsLayout->addWidget(new QCheckBox("Advanced Search tab."),3,0);
    tabsLayout->addWidget(new QCheckBox("Favorities"),4,0);
    tabsGroup->setLayout(tabsLayout);

    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

void StylesPage::save(){

}
StylesPage::StylesPage(QSettings* setting,QWidget *parent)
        : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QGroupBox *configGroup = new QGroupBox(tr("Styles"));
    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addWidget(new QCheckBox("Maximize Box"),0,0);
    groupLayout->addWidget(new QCheckBox("Maximize"),1,0);
    groupLayout->addWidget(new QCheckBox("Pop-up"),2,0);
    groupLayout->addWidget(new QCheckBox("System Menu"),3,0);
    groupLayout->addWidget(new QCheckBox("Clip Child Windows"),4,0);
    groupLayout->addWidget(new QCheckBox("Clip Sibling Windows"),5,0);
    groupLayout->addWidget(new QCheckBox("Horizontal"),6,0);

    groupLayout->addWidget(new QCheckBox("Minimize Box"),0,1);
    groupLayout->addWidget(new QCheckBox("Minimize"),1,1);
    groupLayout->addWidget(new QCheckBox("Vertical Scroll"),2,1);
    groupLayout->addWidget(new QCheckBox("Child Window"),3,1);

    groupLayout->addWidget(new QCheckBox("Border"),0,2);
    groupLayout->addWidget(new QCheckBox("Dlg Frame"),1,2);
    groupLayout->addWidget(new QCheckBox("Visiable"),2,2);
    groupLayout->addWidget(new QCheckBox("Overlapped"),3,2);
    groupLayout->addWidget(new QCheckBox("Thick Frame"),4,2);
    groupLayout->addWidget(new QCheckBox("Disabled"),5,2);

    configGroup->setLayout(groupLayout);
    mainLayout->addWidget(configGroup);

    QGroupBox *tabsGroup = new QGroupBox(tr("Extend Styles"));
    QGridLayout *tabsLayout = new QGridLayout;
    tabsLayout->addWidget(new QCheckBox("Tool Window"),0,0);
    tabsLayout->addWidget(new QCheckBox("Client Edge"),1,0);
    tabsLayout->addWidget(new QCheckBox("Static Edge"),2,0);
    tabsLayout->addWidget(new QCheckBox("Right-aligned Text"),3,0);
    tabsLayout->addWidget(new QCheckBox("Right-to-Left"),4,0);
    tabsLayout->addWidget(new QCheckBox("Control Parent Window"),5,0);

    tabsLayout->addWidget(new QCheckBox("Accept Files"),0,1);
    tabsLayout->addWidget(new QCheckBox("Topmost"),1,1);
    tabsLayout->addWidget(new QCheckBox("Context Help"),2,1);

    tabsLayout->addWidget(new QCheckBox("No Parent Notify"),0,2);
    tabsLayout->addWidget(new QCheckBox("Left Scroll Bar"),1,2);
    tabsLayout->addWidget(new QCheckBox("Transparent"),2,2);

    tabsGroup->setLayout(tabsLayout);

    mainLayout->addWidget(tabsGroup);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

void MergePage::save(){
    QStringList datas;
    for(int i=0;i<listWidget->count();i++){
        datas.append(listWidget->item(i)->text());
    }
    settings->setValue(MERGE_FILES_KEY,datas);
}

MergePage::MergePage(QSettings* setting, QWidget *parent)
        : QWidget(parent)
{
    settings = setting;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel("Merge Files:"),0,0);

    QVBoxLayout *btnsLayout = new QVBoxLayout;

    QPushButton* addButton = new QPushButton(tr("Add"));
    QPushButton* removeButton = new QPushButton(tr("Remove"));
    connect(addButton,SIGNAL(clicked()),this,SLOT(add()));
    connect(removeButton,SIGNAL(clicked()),this,SLOT(remove()));
    btnsLayout->addWidget(addButton);
    btnsLayout->addWidget(removeButton);
    btnsLayout->addStretch(1);

    listWidget = new QListWidget;
    mainLayout->addWidget(listWidget,1,0);
    mainLayout->addLayout(btnsLayout,1,1);
    QStringList mergeList = settings->value(MERGE_FILES_KEY).toStringList();
    foreach(QString value,mergeList){
        QListWidgetItem* item = new QListWidgetItem(value,listWidget);
        listWidget->addItem(item);
    }
    setLayout(mainLayout);
}
void MergePage::add()
{
    QString result = QFileDialog::getOpenFileName(this,tr("Open"),tr("chm File"),tr("CHM File (*.chm)"));
    if(result!=QString::null){
        QFileInfo fileInfo(result);
        QListWidgetItem* item = new QListWidgetItem(fileInfo.fileName(),listWidget);
        listWidget->addItem(item);
    }
}
void MergePage::remove()
{
    QListWidgetItem* item = listWidget->takeItem(listWidget->currentIndex().row());
    if(item!=0)
        delete item;
}
