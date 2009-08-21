#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H

#include <QtGui>
#include "pages.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
QT_END_NAMESPACE

//! [0]
class NewWizard : public QWizard
{
    Q_OBJECT

public:
    NewWizard(QWidget *parent = 0);

    void accept();
    QString getWizardName();
    private:
    QString name;
    QSettings* settings;
};
//! [0]

//! [1]
class SettingPage : public QWizardPage
{
    Q_OBJECT

public:
    SettingPage(QWidget *parent = 0);

private:
    QLabel *label;
    QTabWidget* tabWidget;
};
//! [1]

//! [2]
class NamePage : public QWizardPage
{
    Q_OBJECT

public:
    NamePage(QWidget *parent = 0);

private:
    QLabel *classNameLabel;
    QLabel *baseClassLabel;
    QLineEdit *classNameLineEdit;
    QLineEdit *baseClassLineEdit;
    QCheckBox *qobjectMacroCheckBox;
    QGroupBox *groupBox;
    QRadioButton *qobjectCtorRadioButton;
    QRadioButton *qwidgetCtorRadioButton;
    QRadioButton *defaultCtorRadioButton;
    QCheckBox *copyCtorCheckBox;
};
//! [2]

//! [3]
class CodeStylePage : public QWizardPage
{
    Q_OBJECT

public:
    CodeStylePage(QWidget *parent = 0);

protected:
    void initializePage();

private:
    QCheckBox *commentCheckBox;
    QCheckBox *protectCheckBox;
    QCheckBox *includeBaseCheckBox;
    QLabel *macroNameLabel;
    QLabel *baseIncludeLabel;
    QLineEdit *macroNameLineEdit;
    QLineEdit *baseIncludeLineEdit;
};
//! [3]

class OutputFilesPage : public QWizardPage
{
    Q_OBJECT

public:    
    OutputFilesPage(QWidget *parent = 0);

protected:
    void initializePage();

private:
    QLabel *outputDirLabel;
    QLabel *headerLabel;
    QLabel *implementationLabel;
    QLineEdit *outputDirLineEdit;
    QLineEdit *headerLineEdit;
    QLineEdit *implementationLineEdit;
};

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

protected:
    void initializePage();

private:
    QLabel *label;
};

#endif
