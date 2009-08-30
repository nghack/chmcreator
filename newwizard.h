#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H

#include <QtGui>
#include "qlocalemap.h"
#include "global.h"


class NewWizard : public QWizard
{
    Q_OBJECT

public:
    NewWizard(QWidget *parent = 0);
    void accept();
    const QSettings* getSettings(){return settings;}
    const QString getWizardName(){return name;}
private:
    QString name;
    QSettings* settings;
    QComboBox* languageBox;
};

class SettingPage : public QWizardPage
{
    Q_OBJECT

public:
    SettingPage(QSettings* setting,QWidget *parent = 0);
protected:
    virtual void initializePage();
private:
    QLabel *label;
    QTabWidget* tabWidget;

    QLineEdit *fileNameEdit;
    QLineEdit* targetNameEdit;
    QLineEdit *contentsNameEdit;
    QLineEdit *indexNameEdit;
    QLineEdit *defaultValueLabel;
    QLineEdit* fontEditor;

    QSettings* setting;
public slots:
    void getFont();
};

class NamePage : public QWizardPage
{
    Q_OBJECT

public:
    NamePage(QWidget *parent = 0);
};

#endif
