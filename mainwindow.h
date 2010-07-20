#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QWebView>

#include "global.h"

#include "newwizard.h"
#include "chmproject.h"
#include "QTreeModel.h"
#include "QHHCParser.h"
#include "qtreemodelhandler.h"
#include "qTreeItem.h"
#include "QTreeModel.h"
#include "chmproject.h"
//#include "qtabeditor.h"
#include "qchm.h"
#include "colorlisteditor.h"
#include "configdialog.h"
#include "qcontentstreeview.h"
#include "qmodifyfiledialog.h"
#include "qreplacefilesdialog.h"
#include "qhtmleditor.h"
#include "qfinddialog.h"
#include "qsendmaildialog.h"

namespace Ui
{
    class MainWindow;
}
using namespace QtConcurrent;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QString app,QWidget *parent = 0);
    void loadProject(const QString& proFile);
    void loadDir(const QString& proFile);
    ~MainWindow();
    void saveHHC();
    static void copy(QString from,QString to);
    static void copyDir(QString from,QString to);
    static void copyDirFiles(QString from,QString to);
protected:
    virtual void closeEvent(QCloseEvent *e);
private:
    QTextEdit* currentHTMLEdit();
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);


    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    void createMenus();
    void createToolBar();
    Ui::MainWindow *ui;
    QString myapp;
    QString extractChmFile(QString fileName);
    void createNewWizard();
    QToolBar *fileToolBar;
    QToolBar *compileToolBar;
    QToolBar *editorFileToolBar;
    QToolBar *editorEditToolBar;
    QToolBar *editorFormatToolBar;
    QToolBar *editorFormatTwoToolBar;

    QAction *newProjectAct;
    QAction *openProjectAct;
    QAction *saveProjectAct;

    QAction *compileProjectAct;
    QAction *viewProjectAct;

    QDockWidget* dockProject;
    QDockWidget* dockIndex;
    QDockWidget* dockConsole;

    //QTabEditor* centerView;
    NewWizard wizard;
    QRect rect;

    QVector<CHMProject*> projects;
    CHMProject* currentProject;

    QProcess* pro;
    QMdiArea mdiArea;
    QProjectPropertiesDialog* property;

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
    QWidget *centralWidget;
    QAction *recentFileActs[5];


    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_View;
    QMenu *menu_Test;
    QMenu *menuT_ool;
    QMenu *menu_Help;
    QMenu *menu_Edit;
    QMenu *menu_Project;

    QStatusBar *statusBar;

    QReplaceFilesDialog* repalceFilesDialog;
    FindDialog* findDialog;

    QProgressDialog* compileProcessDialog;
    QSendMailDialog* sendMailDialog;
    QString rsrcPath;

    QAction    *actionSave;

    QAction    *actionTextFormat;
    QAction    *actionTextBold;
    QAction    *actionTextUnderline;
    QAction    *actionTextItalic;
    QAction    *actionTextColor;
    QAction    *actionAlignLeft;
    QAction    *actionAlignCenter;
    QAction    *actionAlignRight;
    QAction    *actionAlignJustify;
    QAction    *actionUndo;
    QAction    *actionRedo;
    QAction    *actionCut;
    QAction    *actionPrint;
    QAction    *actionToPDF;

    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QComboBox *encoding;

    QString fileName;
    QTextEdit *textEdit;

    QTabBar *tabBar;
    QMenu* tabMenu;
    QMenu* formatMenu;
    QContentsTreeView* viewTree;
    QList<QByteArray> encodeList;
private slots:
    void on_actionShow_File_Column_triggered();
    void on_actionSave_As_triggered();
    void subWindowActivated(QMdiSubWindow*);
    void on_actionDirectory_As_Project_triggered();
    void on_actionSuggestion_triggered();
    void on_action_Replace_triggered();
    void on_actionSelect_All_triggered();
    void on_actionDelete_triggered();
    void on_action_Redo_triggered();
    void on_action_Undo_triggered();
    void on_actionPaste_triggered();
    void on_actionCopy_triggered();
    void on_action_Cut_triggered();
    void on_actionClose_Project_triggered();
    void on_actionReplace_In_Files_triggered();
    void on_actionExit_triggered();
    void on_action_Save_triggered();
    void on_action_NewItem_triggered();
    void on_action_Property_triggered();
    void on_action_Run_triggered();
    void on_action_Compile_triggered();
    void compile();
    void on_action_Build_triggered();
    void on_actionStatusBar_triggered();
    void on_actionToolBar_triggered();
    void on_action_New_triggered();
    void on_action_Open_triggered();
    void on_action_About_triggered();
    void on_action_NewAccepted_triggered();
    void console(int value);
    void updateCompileText();
    void updateMenus();
    void updateActionStatus();
    void openTabMenu(const QPoint& pos);
    void encodeChange(QString encode);
    void onModelChange();
public slots:
    void on_action_TreeView_Clicked_triggered(const QModelIndex &index);
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();

    void textFormat();
    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void textAlign(QAction *a);

    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void clipboardDataChanged();
    void printPreview(QPrinter *);
};

#endif // MAINWINDOW_H
