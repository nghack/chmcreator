#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QtGui>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
QT_END_NAMESPACE

//! [0]
class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    GeneralTab(const QFileInfo &fileInfo, QWidget *parent = 0);
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
//! [3]

#endif
