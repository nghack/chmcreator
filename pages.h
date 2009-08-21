#ifndef PAGES_H
#define PAGES_H

#include <QtGui>
#include "chmproject.h"

class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    GeneralTab(QSettings* setting=0,QWidget *parent = 0);
};

class ConfigurationPage : public QWidget
{
public:
    ConfigurationPage(QWidget *parent = 0);
};

class QueryPage : public QWidget
{
public:
    QueryPage(QWidget *parent = 0);
};

class UpdatePage : public QWidget
{
public:
    UpdatePage(QWidget *parent = 0);
};
//! [0]


//! [1]
class FilesTab : public QWidget
{
    Q_OBJECT

public:
    FilesTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};
//! [1]


//! [2]
class ComplierTab : public QWidget
{
    Q_OBJECT

public:
    ComplierTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};

class WindowTab : public QWidget
{
    Q_OBJECT

public:
    WindowTab(const QFileInfo &fileInfo, QWidget *parent = 0);
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
