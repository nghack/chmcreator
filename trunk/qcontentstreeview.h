#ifndef QCONTENTSTREEVIEW_H
#define QCONTENTSTREEVIEW_H

#include <QtGui>
#include "QTreeItem.h"

class QContentsTreeView : public QTreeView
{
public:
    QContentsTreeView();
    ~QContentsTreeView();
    void createActions();
    void mouseReleaseEvent(QMouseEvent *event);
private:
     QMenu* menu;

     QAction *openAct;
     QAction *newAct;
     QAction *addExistingAct;
     QAction *copyAct;
     QAction *pasteAct;
     QAction *deleteAct;
     QAction *renameAct;
     QAction *propertyAct;
};

#endif // QCONTENTSTREEVIEW_H
