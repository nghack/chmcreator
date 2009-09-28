#ifndef PAGES_H
#define PAGES_H

#include <QtGui>
#include "chmproject.h"
#include "qlocalemap.h"
#include "global.h"
#include "qmodifyfiledialog.h"

class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    GeneralTab(QSettings* setting=0,QWidget *parent = 0);

    QLineEdit *fileNameEdit;
    QLineEdit *targetNameEdit;
    QLineEdit *contentsNameEdit;
    QLineEdit *indexNameEdit;
    QLineEdit *logNameEdit;
    QComboBox *pathValueLabel;
    QLineEdit* fontBox;
    QComboBox* languageBox;
    void save();
    QSettings* settings;
    QModifyFileDialog* modifyFileDialog;
    QPushButton* butn;
private slots:
    void setFont();
    void setDefaultFile();
};

class ButtonsPage : public QWidget
{
public:
    ButtonsPage(QSettings* setting,QWidget *parent = 0);
    void save();
};

class WindowPage : public QWidget
{
public:
    WindowPage(QSettings* setting,QWidget *parent = 0);
    void save();
};

class ComplierPage : public QWidget
{
public:
    ComplierPage(QSettings* setting,QWidget *parent = 0);
    void save();
private:
    QSettings* settings;
    QComboBox* compatibiBox;
    QCheckBox* dontIncludeFolder;// = new QCheckBox(tr("Don't Include Folder in Compiled File."));
    QCheckBox* enhancedDecomp;// = new QCheckBox(tr("Support Enhanced Decompliation."));
    QCheckBox* fullSearchSpt;// = new QCheckBox(tr("Full Text Search Support."));
    QCheckBox* binaryIndex;// = new QCheckBox(tr("Create Binary Index."));
    QCheckBox* binaryToc;// = new QCheckBox(tr("Create Binary TOC(Large TOC File.)"));
};
//! [0]


//! [1]
class PositionPage : public QWidget
{
    Q_OBJECT

public:
    PositionPage(QSettings* setting, QWidget *parent = 0);
    void save();
};
//! [1]


//! [2]
class NavPage : public QWidget
{
    Q_OBJECT

public:
    NavPage(QSettings* setting,QWidget *parent = 0);
    void save();
};

class StylesPage : public QWidget
{
    Q_OBJECT

public:
    StylesPage(QSettings* setting,QWidget *parent = 0);
    void save();
};

class MergePage : public QWidget
{
    Q_OBJECT

    QListWidget* listWidget;
public:
    MergePage(QSettings* setting, QWidget *parent = 0);
    void save();
    QSettings* settings;
private slots:
    void add();
    void remove();
};

/*class QPropertyDialog : public QDialog
{
    Q_OBJECT

public:
    QPropertyDialog(const QString &fileName, QWidget *parent = 0);
    void save();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
};*/
#endif
