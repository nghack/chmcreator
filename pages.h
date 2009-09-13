#ifndef PAGES_H
#define PAGES_H

#include <QtGui>
#include "chmproject.h"
#include "qlocalemap.h"
#include "global.h"

class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    GeneralTab(QSettings* setting=0,QWidget *parent = 0);
};

class ButtonsPage : public QWidget
{
public:
    ButtonsPage(QSettings* setting,QWidget *parent = 0);
};

class WindowPage : public QWidget
{
public:
    WindowPage(QSettings* setting,QWidget *parent = 0);
};

class ComplierPage : public QWidget
{
public:
    ComplierPage(QSettings* setting,QWidget *parent = 0);
};
//! [0]


//! [1]
class PositionPage : public QWidget
{
    Q_OBJECT

public:
    PositionPage(QSettings* setting, QWidget *parent = 0);
};
//! [1]


//! [2]
class NavPage : public QWidget
{
    Q_OBJECT

public:
    NavPage(QSettings* setting,QWidget *parent = 0);
};

class StylesPage : public QWidget
{
    Q_OBJECT

public:
    StylesPage(QSettings* setting,QWidget *parent = 0);
};

class MergePage : public QWidget
{
    Q_OBJECT

    QListWidget* listWidget;
public:
    MergePage(QSettings* setting, QWidget *parent = 0);
private slots:
    void add();
    void remove();
};

class QPropertyDialog : public QDialog
{
    Q_OBJECT

public:
    QPropertyDialog(const QString &fileName, QWidget *parent = 0);

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
};
#endif
