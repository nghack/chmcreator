#include <QtGui>

#include "newwizard.h"

NewWizard::NewWizard(QWidget *parent)
    : QWizard(parent)
{
    settings = new QSettings("config/tempProject.ini",QSettings::IniFormat);
    settings->clear();
    QSettings templateSetting("config/template.hhp",QSettings::IniFormat);
    QStringList keyList = templateSetting.allKeys();
    foreach(QString key,keyList){
        settings->setValue(key,templateSetting.value(key));
    }
    addPage(new NamePage);
    addPage(new SettingPage(settings));

    setWindowTitle(tr("New Project"));
}

void NewWizard::accept()
{
    name = field("projectName").toString();

    settings->setValue(PROJECT_EXT_NAME,field("projectName"));

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

    QStringList keylist = settings->allKeys();
    foreach(QString key,keylist)
    {
        qDebug()<<key<<":"<<settings->value(key);
    }
    QDialog::accept();
}

NamePage::NamePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Create a CHM Project");
    setSubTitle("Enter a Project Name.");

    QLabel *projectNameLabel = new QLabel("Project Name:");
    QLineEdit *projectNameLineEdit = new QLineEdit;

    registerField("projectName*", projectNameLineEdit);
    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(projectNameLabel, 0, 0);
    layout1->addWidget(projectNameLineEdit, 0, 1);

    setLayout(layout1);
}

 void SettingPage::getFont()
 {
     bool ok;
     QFont font = QFontDialog::getFont(&ok, QFont(fontEditor->text()), this);
     if (ok) {
         fontEditor->setText(font.toString());
         fontEditor->setFont(font);
     }
 }

SettingPage::SettingPage(QSettings* setting,QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("CHM Setting");
    setSubTitle("Define CHM Build Settings.");

    this->setting = setting;
    tabWidget = new QTabWidget;

    /*************************/
    QWidget* tabGeneral = new QWidget;

    QLabel *fileNameLabel = new QLabel(tr("Title:"));
    fileNameEdit = new QLineEdit(setting->value(PROJECT_TITLE_CHM,tr("CHM File Title")).toString());
    registerField("projectTitle", fileNameEdit);

    QLabel *targetLabel = new QLabel(tr("Compiled File:"));
    targetNameEdit = new QLineEdit;
    registerField("projectTargetName", targetNameEdit);

    QLabel *contentsLabel = new QLabel(tr("Contents File:"));
    contentsNameEdit = new QLineEdit(setting->value(PROJECT_CONT_FILE,tr("index.hhc")).toString());//
    registerField("projectContentsFile", contentsNameEdit);

    QLabel *indexLabel = new QLabel(tr("Indexes File:"));
    indexNameEdit = new QLineEdit(setting->value(PROJECT_INDEX,tr("index.hhk")).toString());
    registerField("projectIndexFile", indexNameEdit);

    QLabel *defaultLabel = new QLabel(tr("Default File:"));
    defaultValueLabel = new QLineEdit(setting->value(PROJECT_DEFAULT_FILE,tr("index.html")).toString());
    registerField("projectDefaultFile", defaultValueLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(fileNameEdit);
    mainLayout->addWidget(targetLabel);
    mainLayout->addWidget(targetNameEdit);
    mainLayout->addWidget(contentsLabel);
    mainLayout->addWidget(contentsNameEdit);
    mainLayout->addWidget(indexLabel);
    mainLayout->addWidget(indexNameEdit);
    mainLayout->addWidget(defaultLabel);
    mainLayout->addWidget(defaultValueLabel);
    mainLayout->addStretch(1);
    tabGeneral->setLayout(mainLayout);

    tabWidget->addTab(tabGeneral,QIcon(""),"General");
    /*************************/
    QWidget* complierGeneral = new QWidget;

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
    registerField("projectComplierVersion", compatibiBox);

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

    registerField("projectIncludeFolder", dontIncludeFolder);
    registerField("projectDecompile", enhancedDecomp);
    registerField("projectFullTextSearch", fullSearchSpt);
    registerField("projectBinaryIndex", binaryIndex);
    registerField("projectBinaryTOC", binaryToc);

    mainComplierLayout->addLayout(compilerLayout);
    mainComplierLayout->addWidget(dontIncludeFolder);
    mainComplierLayout->addWidget(enhancedDecomp);
    mainComplierLayout->addWidget(fullSearchSpt);
    mainComplierLayout->addWidget(binaryIndex);
    mainComplierLayout->addWidget(binaryToc);
    mainComplierLayout->addStretch(1);

    complierGeneral->setLayout(mainComplierLayout);

    tabWidget->addTab(complierGeneral,QIcon(""),"Compiler");
    /***********************************************/
    QWidget* internationalGeneral = new QWidget;

    QVBoxLayout *internationalLayout = new QVBoxLayout;

    QLabel *languageLabel = new QLabel(tr("Language:"));
    QComboBox* languageBox = new QComboBox;
    QLocaleMap localeMap;
    QList<QString> tempContry = localeMap.getLocale().keys();
    foreach(QString contry,tempContry){
        languageBox->addItem(contry);
    }
    languageBox->setCurrentIndex(27);
    registerField("projectLanuage", languageBox);

    QLabel *fontLabel = new QLabel(tr("Font:"));    
    fontEditor = new QLineEdit(setting->value(PROJECT_FONT,"123456").toString());
    registerField("projectFont", fontEditor);

    QPushButton* fontButton = new QPushButton;
    connect(fontButton,SIGNAL(clicked()),this,SLOT(getFont()));

    internationalLayout->addWidget(languageLabel);
    internationalLayout->addWidget(languageBox);

    QHBoxLayout *internationalFontLayout = new QHBoxLayout;
    internationalLayout->addWidget(fontLabel);
    internationalFontLayout->addWidget(fontEditor);
    internationalFontLayout->addWidget(fontButton);//International
    internationalLayout->addLayout(internationalFontLayout);
    internationalLayout->addStretch(1);

    internationalGeneral->setLayout(internationalLayout);
    tabWidget->addTab(internationalGeneral,QIcon(""),"International");
    //////////////////////////////////////////////////
    QVBoxLayout *mainLayout1 = new QVBoxLayout;
    mainLayout1->addWidget(tabWidget);
    setLayout(mainLayout1);
}

void SettingPage::initializePage()
{
    targetNameEdit->setText(field("projectName").toString()+".chm");
    fontEditor->setText(setting->value(PROJECT_FONT,"123456").toString());
}
