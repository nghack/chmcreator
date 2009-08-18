/********************************************************************************
** Form generated from reading ui file 'newdialog.ui'
**
** Created: Tue Aug 11 15:11:17 2009
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NEWDIALOG_H
#define UI_NEWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_NewDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QListWidget *listWidget;

    void setupUi(QDialog *NewDialog)
    {
    if (NewDialog->objectName().isEmpty())
        NewDialog->setObjectName(QString::fromUtf8("NewDialog"));
    NewDialog->setWindowModality(Qt::ApplicationModal);
    NewDialog->resize(277, 264);
    buttonBox = new QDialogButtonBox(NewDialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(100, 230, 171, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    label = new QLabel(NewDialog);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 4, 161, 21));
    listWidget = new QListWidget(NewDialog);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(10, 30, 256, 192));
    QFont font;
    font.setPointSize(12);
    listWidget->setFont(font);

    retranslateUi(NewDialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), NewDialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), NewDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(NewDialog);
    } // setupUi

    void retranslateUi(QDialog *NewDialog)
    {
    NewDialog->setWindowTitle(QApplication::translate("NewDialog", "New", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("NewDialog", "Specify what to create:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(NewDialog);
    } // retranslateUi

};

namespace Ui {
    class NewDialog: public Ui_NewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWDIALOG_H
