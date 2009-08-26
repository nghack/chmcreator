#ifndef QCONTENTSTREEVIEW_H
#define QCONTENTSTREEVIEW_H

#include <QtGui>
#include "QTreeItem.h"
#include "newfiledialog.h"

class MainWindow;
extern QSettings settings;
class QContentsTreeView : public QTreeView
{
    Q_OBJECT
public:
    QContentsTreeView(MainWindow* mainWindow);
    ~QContentsTreeView();
    void createActions();
    void mouseReleaseEvent(QMouseEvent *event);
    void addExistFile(const QString fileName);
private:
     MainWindow* mainWindow;
     QMenu* menu;

     QAction *openAct;
     QAction *newAct;
     QAction *addExistingAct;
     QAction *copyAct;
     QAction *pasteAct;
     QAction *deleteAct;
     QAction *renameAct;
     QAction *propertyAct;

     NewFileDialog dialog;
private slots:
     void openFile();
     void newFile();
     void addExistFiles();
     void copyFile();
     void pasteFile();
     void deleteFile();
     void renameFile();
     void property();
};

#endif // QCONTENTSTREEVIEW_H
