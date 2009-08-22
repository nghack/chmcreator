#include <QtGui>

#include "pages.h"

ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Server configuration"));

    QLabel *serverLabel = new QLabel(tr("Server:"));
    QComboBox *serverCombo = new QComboBox;
    serverCombo->addItem(tr("Trolltech (Australia)"));
    serverCombo->addItem(tr("Trolltech (Germany)"));
    serverCombo->addItem(tr("Trolltech (Norway)"));
    serverCombo->addItem(tr("Trolltech (People's Republic of China)"));
    serverCombo->addItem(tr("Trolltech (USA)"));

    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(serverLabel);
    serverLayout->addWidget(serverCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(serverLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

UpdatePage::UpdatePage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
    QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
    QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
    QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

    QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

    QListWidget *packageList = new QListWidget;
    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
    qtItem->setText(tr("Qt"));
    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
    qsaItem->setText(tr("QSA"));
    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
    teamBuilderItem->setText(tr("Teambuilder"));

    QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

    QVBoxLayout *updateLayout = new QVBoxLayout;
    updateLayout->addWidget(systemCheckBox);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);
    updateGroup->setLayout(updateLayout);

    QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageGroup->setLayout(packageLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

QueryPage::QueryPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QLabel *dateLabel = new QLabel(tr("Released after:"));
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(tr("Return up to "));
    hitsSpinBox->setSuffix(tr(" results"));
    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);

    QPushButton *startQueryButton = new QPushButton(tr("Start query"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(dateLabel, 1, 0);
    packagesLayout->addWidget(dateEdit, 1, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startQueryButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
//#define COMPILED_FILE QString("OPTIONS/Compiled file")
//#define CONTENTS_FILE QString("OPTIONS/Contents file")
//#define INDEX_FILE QString("OPTIONS/Index file")
//#define LOG_FILE QString("OPTIONS/Error log file")
//
//#define INFOTYPES QString("INFOTYPES")
GeneralTab::GeneralTab(QSettings* setting,QWidget *parent)
    : QWidget(parent)
{
    QLabel *fileNameLabel = new QLabel(tr("Title:"));
    QLineEdit *fileNameEdit = new QLineEdit(setting==0?"":setting->value(TITLE).toString());

    QLabel *targetLabel = new QLabel(tr("Compiled File:"));
    QLineEdit *targetNameEdit = new QLineEdit(setting==0?"":setting->value(COMPILED_FILE).toString());

    QLabel *contentsLabel = new QLabel(tr("Contents File:"));
    QLineEdit *contentsNameEdit = new QLineEdit(setting==0?"":setting->value(CONTENTS_FILE).toString());

    QLabel *indexLabel = new QLabel(tr("Indexes File:"));
    QLineEdit *indexNameEdit = new QLineEdit(setting==0?"":setting->value(INDEX_FILE).toString());

    QLabel *logLabel = new QLabel(tr("Log File:"));
    QLineEdit *logNameEdit = new QLineEdit(setting==0?"":setting->value(LOG_FILE).toString());

    QLabel *pathLabel = new QLabel(tr("Default File:"));
    QComboBox *pathValueLabel = new QComboBox();

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
//! [6]

//! [7]
FilesTab::FilesTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *permissionsGroup = new QGroupBox(tr("Permissions"));

    QCheckBox *readable = new QCheckBox(tr("Readable"));
    if (fileInfo.isReadable())
        readable->setChecked(true);

    QCheckBox *writable = new QCheckBox(tr("Writable"));
    if ( fileInfo.isWritable() )
        writable->setChecked(true);

    QCheckBox *executable = new QCheckBox(tr("Executable"));
    if ( fileInfo.isExecutable() )
        executable->setChecked(true);

    QGroupBox *ownerGroup = new QGroupBox(tr("Ownership"));

    QLabel *ownerLabel = new QLabel(tr("Owner"));
    QLabel *ownerValueLabel = new QLabel(fileInfo.owner());
    ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *groupLabel = new QLabel(tr("Group"));
    QLabel *groupValueLabel = new QLabel(fileInfo.group());
    groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *permissionsLayout = new QVBoxLayout;
    permissionsLayout->addWidget(readable);
    permissionsLayout->addWidget(writable);
    permissionsLayout->addWidget(executable);
    permissionsGroup->setLayout(permissionsLayout);

    QVBoxLayout *ownerLayout = new QVBoxLayout;
    ownerLayout->addWidget(ownerLabel);
    ownerLayout->addWidget(ownerValueLabel);
    ownerLayout->addWidget(groupLabel);
    ownerLayout->addWidget(groupValueLabel);
    ownerGroup->setLayout(ownerLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(permissionsGroup);
    mainLayout->addWidget(ownerGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
//! [7]

//! [8]
ComplierTab::ComplierTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
    QLabel *topLabel = new QLabel(tr("Open with:"));

    QListWidget *applicationsListBox = new QListWidget;
    QStringList applications;

    for (int i = 1; i <= 30; ++i)
        applications.append(tr("Application %1").arg(i));
    applicationsListBox->insertItems(0, applications);

    QCheckBox *alwaysCheckBox;

    if (fileInfo.suffix().isEmpty())
        alwaysCheckBox = new QCheckBox(tr("Always use this application to "
            "open this type of file"));
    else
        alwaysCheckBox = new QCheckBox(tr("Always use this application to "
            "open files with the extension '%1'").arg(fileInfo.suffix()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(applicationsListBox);
    layout->addWidget(alwaysCheckBox);
    setLayout(layout);
}
WindowTab::WindowTab(const QFileInfo &fileInfo, QWidget *parent)
        : QWidget(parent)
{
//    QLabel *topLabel = new QLabel(tr("Open with:"));
//
//    QListWidget *applicationsListBox = new QListWidget;
//    QStringList applications;
//
//    for (int i = 1; i <= 30; ++i)
//        applications.append(tr("Application %1").arg(i));
//    applicationsListBox->insertItems(0, applications);
//
//    QCheckBox *alwaysCheckBox;
//
//    if (fileInfo.suffix().isEmpty())
//        alwaysCheckBox = new QCheckBox(tr("Always use this application to "
//                                          "open this type of file"));
//    else
//        alwaysCheckBox = new QCheckBox(tr("Always use this application to "
//                                          "open files with the extension '%1'").arg(fileInfo.suffix()));
//
//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->addWidget(topLabel);
//    layout->addWidget(applicationsListBox);
//    layout->addWidget(alwaysCheckBox);
//    setLayout(layout);
}
