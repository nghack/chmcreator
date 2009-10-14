/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Wed Oct 14 17:38:55 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_New;
    QAction *action_Open;
    QAction *actionClose_Project;
    QAction *actionClose_All;
    QAction *action_Save_Project;
    QAction *actionCo_mpile;
    QAction *actionDecompile;
    QAction *actionChm_Information;
    QAction *actionPr_eference;
    QAction *actionExit;
    QAction *actionToolBar;
    QAction *actionStatusBar;
    QAction *actionCompiled_Help_File;
    QAction *actionHTML_Help_Message;
    QAction *action_About;
    QAction *action_Option;
    QAction *action_Compile;
    QAction *action_Build;
    QAction *action_Undo;
    QAction *action_Redo;
    QAction *actionPr_eference_2;
    QAction *action_Run;
    QAction *action_Property;
    QAction *action_Import;
    QAction *action_Cut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionDelete;
    QAction *actionSelect_All;
    QAction *action_Replace;
    QAction *actionClean;
    QAction *action_Save;
    QAction *actionSave_All;
    QAction *actionReplace_In_Files;
    QAction *actionSuggestion;
    QAction *actionDirectory_As_Project;
    QAction *actionSave_As;
    QAction *actionShow_File_Column;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuImport;
    QMenu *menu_View;
    QMenu *menu_Test;
    QMenu *menu_Help;
    QMenu *menu_Edit;
    QMenu *menu_Project;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/main.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QString::fromUtf8("action_New"));
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        actionClose_Project = new QAction(MainWindow);
        actionClose_Project->setObjectName(QString::fromUtf8("actionClose_Project"));
        actionClose_All = new QAction(MainWindow);
        actionClose_All->setObjectName(QString::fromUtf8("actionClose_All"));
        action_Save_Project = new QAction(MainWindow);
        action_Save_Project->setObjectName(QString::fromUtf8("action_Save_Project"));
        actionCo_mpile = new QAction(MainWindow);
        actionCo_mpile->setObjectName(QString::fromUtf8("actionCo_mpile"));
        actionDecompile = new QAction(MainWindow);
        actionDecompile->setObjectName(QString::fromUtf8("actionDecompile"));
        actionChm_Information = new QAction(MainWindow);
        actionChm_Information->setObjectName(QString::fromUtf8("actionChm_Information"));
        actionPr_eference = new QAction(MainWindow);
        actionPr_eference->setObjectName(QString::fromUtf8("actionPr_eference"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionToolBar = new QAction(MainWindow);
        actionToolBar->setObjectName(QString::fromUtf8("actionToolBar"));
        actionToolBar->setCheckable(true);
        actionToolBar->setChecked(true);
        actionStatusBar = new QAction(MainWindow);
        actionStatusBar->setObjectName(QString::fromUtf8("actionStatusBar"));
        actionStatusBar->setCheckable(true);
        actionStatusBar->setChecked(true);
        actionCompiled_Help_File = new QAction(MainWindow);
        actionCompiled_Help_File->setObjectName(QString::fromUtf8("actionCompiled_Help_File"));
        actionHTML_Help_Message = new QAction(MainWindow);
        actionHTML_Help_Message->setObjectName(QString::fromUtf8("actionHTML_Help_Message"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_Option = new QAction(MainWindow);
        action_Option->setObjectName(QString::fromUtf8("action_Option"));
        action_Compile = new QAction(MainWindow);
        action_Compile->setObjectName(QString::fromUtf8("action_Compile"));
        action_Build = new QAction(MainWindow);
        action_Build->setObjectName(QString::fromUtf8("action_Build"));
        action_Undo = new QAction(MainWindow);
        action_Undo->setObjectName(QString::fromUtf8("action_Undo"));
        action_Redo = new QAction(MainWindow);
        action_Redo->setObjectName(QString::fromUtf8("action_Redo"));
        actionPr_eference_2 = new QAction(MainWindow);
        actionPr_eference_2->setObjectName(QString::fromUtf8("actionPr_eference_2"));
        action_Run = new QAction(MainWindow);
        action_Run->setObjectName(QString::fromUtf8("action_Run"));
        action_Property = new QAction(MainWindow);
        action_Property->setObjectName(QString::fromUtf8("action_Property"));
        action_Import = new QAction(MainWindow);
        action_Import->setObjectName(QString::fromUtf8("action_Import"));
        action_Cut = new QAction(MainWindow);
        action_Cut->setObjectName(QString::fromUtf8("action_Cut"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
        action_Replace = new QAction(MainWindow);
        action_Replace->setObjectName(QString::fromUtf8("action_Replace"));
        actionClean = new QAction(MainWindow);
        actionClean->setObjectName(QString::fromUtf8("actionClean"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        actionSave_All = new QAction(MainWindow);
        actionSave_All->setObjectName(QString::fromUtf8("actionSave_All"));
        actionReplace_In_Files = new QAction(MainWindow);
        actionReplace_In_Files->setObjectName(QString::fromUtf8("actionReplace_In_Files"));
        actionSuggestion = new QAction(MainWindow);
        actionSuggestion->setObjectName(QString::fromUtf8("actionSuggestion"));
        actionDirectory_As_Project = new QAction(MainWindow);
        actionDirectory_As_Project->setObjectName(QString::fromUtf8("actionDirectory_As_Project"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionShow_File_Column = new QAction(MainWindow);
        actionShow_File_Column->setObjectName(QString::fromUtf8("actionShow_File_Column"));
        actionShow_File_Column->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 18));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuImport = new QMenu(menu_File);
        menuImport->setObjectName(QString::fromUtf8("menuImport"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        menu_Test = new QMenu(menuBar);
        menu_Test->setObjectName(QString::fromUtf8("menu_Test"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menu_Edit = new QMenu(menuBar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        menu_Project = new QMenu(menuBar);
        menu_Project->setObjectName(QString::fromUtf8("menu_Project"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Edit->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menuBar->addAction(menu_Project->menuAction());
        menuBar->addAction(menu_Test->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_New);
        menu_File->addAction(action_Open);
        menu_File->addAction(actionClose_Project);
        menu_File->addSeparator();
        menu_File->addAction(action_Save);
        menu_File->addAction(actionSave_As);
        menu_File->addSeparator();
        menu_File->addAction(menuImport->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionExit);
        menu_File->addSeparator();
        menuImport->addAction(actionDirectory_As_Project);
        menu_View->addAction(actionToolBar);
        menu_View->addAction(actionStatusBar);
        menu_View->addSeparator();
        menu_View->addAction(actionShow_File_Column);
        menu_Test->addAction(action_Compile);
        menu_Test->addSeparator();
        menu_Test->addAction(action_Run);
        menu_Help->addAction(action_About);
        menu_Help->addAction(actionSuggestion);
        menu_Edit->addAction(action_Undo);
        menu_Edit->addAction(action_Redo);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Cut);
        menu_Edit->addAction(actionCopy);
        menu_Edit->addAction(actionPaste);
        menu_Edit->addSeparator();
        menu_Edit->addAction(actionSelect_All);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Replace);
        menu_Edit->addAction(actionReplace_In_Files);
        menu_Project->addAction(action_Property);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_New->setText(QApplication::translate("MainWindow", "&New", 0, QApplication::UnicodeUTF8));
        action_New->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        action_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionClose_Project->setText(QApplication::translate("MainWindow", "Close &Project", 0, QApplication::UnicodeUTF8));
        actionClose_All->setText(QApplication::translate("MainWindow", "&Close All", 0, QApplication::UnicodeUTF8));
        action_Save_Project->setText(QApplication::translate("MainWindow", "&Save Project", 0, QApplication::UnicodeUTF8));
        action_Save_Project->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionCo_mpile->setText(QApplication::translate("MainWindow", "Co&mpile...", 0, QApplication::UnicodeUTF8));
        actionCo_mpile->setShortcut(QApplication::translate("MainWindow", "Ctrl+F5", 0, QApplication::UnicodeUTF8));
        actionDecompile->setText(QApplication::translate("MainWindow", "&Decompile...", 0, QApplication::UnicodeUTF8));
        actionChm_Information->setText(QApplication::translate("MainWindow", "Chm &Information", 0, QApplication::UnicodeUTF8));
        actionPr_eference->setText(QApplication::translate("MainWindow", "Pr&eference", 0, QApplication::UnicodeUTF8));
        actionPr_eference->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionToolBar->setText(QApplication::translate("MainWindow", "ToolBar", 0, QApplication::UnicodeUTF8));
        actionStatusBar->setText(QApplication::translate("MainWindow", "StatusBar", 0, QApplication::UnicodeUTF8));
        actionCompiled_Help_File->setText(QApplication::translate("MainWindow", "Compiled Help File...", 0, QApplication::UnicodeUTF8));
        actionHTML_Help_Message->setText(QApplication::translate("MainWindow", "HTML Help Message", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        action_Option->setText(QApplication::translate("MainWindow", "&Preference", 0, QApplication::UnicodeUTF8));
        action_Compile->setText(QApplication::translate("MainWindow", "&Compile", 0, QApplication::UnicodeUTF8));
        action_Build->setText(QApplication::translate("MainWindow", "&Build", 0, QApplication::UnicodeUTF8));
        action_Undo->setText(QApplication::translate("MainWindow", "&Undo", 0, QApplication::UnicodeUTF8));
        action_Undo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        action_Redo->setText(QApplication::translate("MainWindow", "&Redo", 0, QApplication::UnicodeUTF8));
        action_Redo->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        actionPr_eference_2->setText(QApplication::translate("MainWindow", "&Find", 0, QApplication::UnicodeUTF8));
        action_Run->setText(QApplication::translate("MainWindow", "&Run", 0, QApplication::UnicodeUTF8));
        action_Run->setShortcut(QApplication::translate("MainWindow", "F5", 0, QApplication::UnicodeUTF8));
        action_Property->setText(QApplication::translate("MainWindow", "&Properties", 0, QApplication::UnicodeUTF8));
        action_Property->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        action_Import->setText(QApplication::translate("MainWindow", "&Import", 0, QApplication::UnicodeUTF8));
        action_Import->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        action_Cut->setText(QApplication::translate("MainWindow", "&Cut", 0, QApplication::UnicodeUTF8));
        action_Cut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0, QApplication::UnicodeUTF8));
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0, QApplication::UnicodeUTF8));
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        actionDelete->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0, QApplication::UnicodeUTF8));
        actionSelect_All->setText(QApplication::translate("MainWindow", "Select All", 0, QApplication::UnicodeUTF8));
        actionSelect_All->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        action_Replace->setText(QApplication::translate("MainWindow", "&Find/Replace", 0, QApplication::UnicodeUTF8));
        action_Replace->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        actionClean->setText(QApplication::translate("MainWindow", "Clean Project", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        action_Save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSave_All->setText(QApplication::translate("MainWindow", "Save All", 0, QApplication::UnicodeUTF8));
        actionReplace_In_Files->setText(QApplication::translate("MainWindow", "Replace In Files", 0, QApplication::UnicodeUTF8));
        actionSuggestion->setText(QApplication::translate("MainWindow", "Suggestion to us", 0, QApplication::UnicodeUTF8));
        actionDirectory_As_Project->setText(QApplication::translate("MainWindow", "Directory As Project", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As...", 0, QApplication::UnicodeUTF8));
        actionShow_File_Column->setText(QApplication::translate("MainWindow", "Show File Column", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
        menu_Test->setTitle(QApplication::translate("MainWindow", "&Build", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        menu_Project->setTitle(QApplication::translate("MainWindow", "&Project", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
