#include <QtGui>

#include "pages.h"

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

ComplierPage::ComplierPage(QSettings* setting,QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *compilerLayout = new QHBoxLayout;
    compilerLayout->addWidget(new QLabel(tr("Compatibility:")));

    QComboBox* compatibiBox = new QComboBox;
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

    QCheckBox* dontIncludeFolder = new QCheckBox(tr("Don't Include Folder in Compiled File."));
    QCheckBox* enhancedDecomp = new QCheckBox(tr("Support Enhanced Decompliation."));
    QCheckBox* fullSearchSpt = new QCheckBox(tr("Full Text Search Support."));
    QCheckBox* binaryIndex = new QCheckBox(tr("Create Binary Index."));
    QCheckBox* binaryToc = new QCheckBox(tr("Create Binary TOC(Large TOC File.)"));

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

}

GeneralTab::GeneralTab(QSettings* setting,QWidget *parent)
    : QWidget(parent)
{
    QLabel *fileNameLabel = new QLabel(tr("Title:"));
    QLineEdit *fileNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_TITLE_CHM).toString());

    QLabel *targetLabel = new QLabel(tr("Compiled File:"));
    QLineEdit *targetNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_TARGET).toString());

    QLabel *contentsLabel = new QLabel(tr("Contents File:"));
    QLineEdit *contentsNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_CONT_FILE).toString());

    QLabel *indexLabel = new QLabel(tr("Indexes File:"));
    QLineEdit *indexNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_INDEX).toString());

    QLabel *logLabel = new QLabel(tr("Log File:"));
    QLineEdit *logNameEdit = new QLineEdit(setting==0?"":setting->value(PROJECT_LOG_FILE).toString());

    QLabel *pathLabel = new QLabel(tr("Default File:"));
    QComboBox *pathValueLabel = new QComboBox();

    QDir directory = QDir(setting->value(PROJECT_PATH).toString());
    directory.setCurrent(setting->value(PROJECT_PATH).toString());
    pathValueLabel->addItems(directory.entryList(QStringList("*"),
                                QDir::Files | QDir::NoSymLinks | QDir::AllDirs));


    QLabel *sizeLabel = new QLabel(tr("Default Window:"));
    QComboBox *sizeValueLabel = new QComboBox;

    QGroupBox* groupBox = new QGroupBox;
    groupBox->setTitle(tr("International Setting"));

    QGridLayout *groupLayout = new QGridLayout;

    QLabel *languageLabel = new QLabel(tr("Language:"));
    QComboBox* languageBox = new QComboBox;
    QLocaleMap localeMap;
    QList<QString> tempContry = localeMap.getLocale().keys();
    foreach(QString contry,tempContry){
        languageBox->addItem(contry);
    }

    QLabel *fontLabel = new QLabel(tr("Font:"));
    QLineEdit* fontBox = new QLineEdit;
    QPushButton* fontButton = new QPushButton;

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
    mainLayout->addWidget(pathValueLabel);
    mainLayout->addWidget(sizeLabel);
    mainLayout->addWidget(sizeValueLabel);
    mainLayout->addWidget(groupBox);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

//! [7]
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
    tabsLayout->addWidget(new QCheckBox("Right-to-Left Reading Order"),4,0);
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
MergePage::MergePage(QSettings* setting, QWidget *parent)
        : QWidget(parent)
{
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

    setLayout(mainLayout);
}
void MergePage::add()
{
    QString result = QFileDialog::getOpenFileName(0,"Open");
    if(result!=QString::null){
        QListWidgetItem* item = new QListWidgetItem(result,listWidget);
        listWidget->addItem(item);
    }
}
void MergePage::remove()
{
    QListWidgetItem* item = listWidget->takeItem(listWidget->currentIndex().row());
    if(item!=0)
        delete item;
}