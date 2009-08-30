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
    void keyPressEvent(QKeyEvent *e);
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

     QAction *moveUpAct;
     QAction *moveDownAct;

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

     void moveUp();
     void moveDown();

     void property();
public slots:
     void clear();
     void headerClicked(const QModelIndex& index);
 signals:
     void changed(const QMimeData *mimeData = 0);

// protected:
//     void dragEnterEvent(QDragEnterEvent *event);
//     void dragMoveEvent(QDragMoveEvent *event);
//     void dragLeaveEvent(QDragLeaveEvent *event);
//     void dropEvent(QDropEvent *event);

};

#endif // QCONTENTSTREEVIEW_H