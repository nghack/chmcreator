#include <QtGui>

#include "newwizard.h"

//! [0] //! [1]
NewWizard::NewWizard(QWidget *parent)
    : QWizard(parent)
{
    addPage(new TypePage);
    addPage(new NamePage);
//    addPage(new CodeStylePage);
//    addPage(new OutputFilesPage);
//    addPage(new ConclusionPage);

    setWindowTitle(tr("New Wizard"));
//! [2]
}
//! [1] //! [2]

//! [3]
QString NewWizard::getWizardName(){
    return name;
}
void NewWizard::accept()
{
    name = field("projectName").toString();
    QDialog::accept();
}
//! [6]

//! [7]
TypePage::TypePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Select a Wizard");
    setSubTitle("Select a Wizard");

    QLabel *projectNameLabel1 = new QLabel("Project Name:");
    QListWidget *projectNameLineEdit1 = new QListWidget;

    QVBoxLayout *layout0 = new QVBoxLayout;
    QStringList list;
    list.append("Chm Project");
    list.append("Text");
    list.append("HTML File");

    projectNameLineEdit1->addItems(list);
    projectNameLineEdit1->item(0)->setSelected(true);

    layout0->addWidget(projectNameLabel1);
    layout0->addWidget(projectNameLineEdit1);
    setLayout(layout0);
}
//! [7]

//! [8] //! [9]
NamePage::NamePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Create A Chm Project");
    setSubTitle("Enter a Project Name.");

    QLabel *projectNameLabel = new QLabel("Project Name:");
    QLineEdit *projectNameLineEdit = new QLineEdit;

    registerField("projectName*", projectNameLineEdit);
    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(projectNameLabel, 0, 0);
    layout1->addWidget(projectNameLineEdit, 0, 1);

    setLayout(layout1);
}
//! [13]

//! [14]
CodeStylePage::CodeStylePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Code Style Options"));
    setSubTitle(tr("Choose the formatting of the generated code."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo2.png"));

    commentCheckBox = new QCheckBox(tr("&Start generated files with a "
//! [14]
                                       "comment"));
    commentCheckBox->setChecked(true);

    protectCheckBox = new QCheckBox(tr("&Protect header file against multiple "
                                       "inclusions"));
    protectCheckBox->setChecked(true);

    macroNameLabel = new QLabel(tr("&Macro name:"));
    macroNameLineEdit = new QLineEdit;
    macroNameLabel->setBuddy(macroNameLineEdit);

    includeBaseCheckBox = new QCheckBox(tr("&Include base class definition"));
    baseIncludeLabel = new QLabel(tr("Base class include:"));
    baseIncludeLineEdit = new QLineEdit;
    baseIncludeLabel->setBuddy(baseIncludeLineEdit);

    connect(protectCheckBox, SIGNAL(toggled(bool)),
            macroNameLabel, SLOT(setEnabled(bool)));
    connect(protectCheckBox, SIGNAL(toggled(bool)),
            macroNameLineEdit, SLOT(setEnabled(bool)));
    connect(includeBaseCheckBox, SIGNAL(toggled(bool)),
            baseIncludeLabel, SLOT(setEnabled(bool)));
    connect(includeBaseCheckBox, SIGNAL(toggled(bool)),
            baseIncludeLineEdit, SLOT(setEnabled(bool)));

    registerField("comment", commentCheckBox);
    registerField("protect", protectCheckBox);
    registerField("macroName", macroNameLineEdit);
    registerField("includeBase", includeBaseCheckBox);
    registerField("baseInclude", baseIncludeLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(0, 20);
    layout->addWidget(commentCheckBox, 0, 0, 1, 3);
    layout->addWidget(protectCheckBox, 1, 0, 1, 3);
    layout->addWidget(macroNameLabel, 2, 1);
    layout->addWidget(macroNameLineEdit, 2, 2);
    layout->addWidget(includeBaseCheckBox, 3, 0, 1, 3);
    layout->addWidget(baseIncludeLabel, 4, 1);
    layout->addWidget(baseIncludeLineEdit, 4, 2);
//! [15]
    setLayout(layout);
}
//! [15]

//! [16]
void CodeStylePage::initializePage()
{
    QString className = field("className").toString();
    macroNameLineEdit->setText(className.toUpper() + "_H");

    QString baseClass = field("baseClass").toString();

    includeBaseCheckBox->setChecked(!baseClass.isEmpty());
    includeBaseCheckBox->setEnabled(!baseClass.isEmpty());
    baseIncludeLabel->setEnabled(!baseClass.isEmpty());
    baseIncludeLineEdit->setEnabled(!baseClass.isEmpty());

    if (baseClass.isEmpty()) {
        baseIncludeLineEdit->clear();
    } else if (QRegExp("Q[A-Z].*").exactMatch(baseClass)) {
        baseIncludeLineEdit->setText("<" + baseClass + ">");
    } else {
        baseIncludeLineEdit->setText("\"" + baseClass.toLower() + ".h\"");
    }
}
//! [16]

OutputFilesPage::OutputFilesPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Output Files"));
    setSubTitle(tr("Specify where you want the wizard to put the generated "
                   "skeleton code."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo3.png"));

    outputDirLabel = new QLabel(tr("&Output directory:"));
    outputDirLineEdit = new QLineEdit;
    outputDirLabel->setBuddy(outputDirLineEdit);

    headerLabel = new QLabel(tr("&Header file name:"));
    headerLineEdit = new QLineEdit;
    headerLabel->setBuddy(headerLineEdit);

    implementationLabel = new QLabel(tr("&Implementation file name:"));
    implementationLineEdit = new QLineEdit;
    implementationLabel->setBuddy(implementationLineEdit);

    registerField("outputDir*", outputDirLineEdit);
    registerField("header*", headerLineEdit);
    registerField("implementation*", implementationLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(outputDirLabel, 0, 0);
    layout->addWidget(outputDirLineEdit, 0, 1);
    layout->addWidget(headerLabel, 1, 0);
    layout->addWidget(headerLineEdit, 1, 1);
    layout->addWidget(implementationLabel, 2, 0);
    layout->addWidget(implementationLineEdit, 2, 1);
    setLayout(layout);
}

//! [17]
void OutputFilesPage::initializePage()
{
    QString className = field("className").toString();
    headerLineEdit->setText(className.toLower() + ".h");
    implementationLineEdit->setText(className.toLower() + ".cpp");
    outputDirLineEdit->setText(QDir::convertSeparators(QDir::tempPath()));
}
//! [17]

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Conclusion"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark2.png"));

    label = new QLabel;
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

void ConclusionPage::initializePage()
{
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Click %1 to generate the class skeleton.")
                   .arg(finishText));
}
