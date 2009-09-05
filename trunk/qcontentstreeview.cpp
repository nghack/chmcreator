#include "qcontentstreeview.h"
#include "mainwindow.h"
#include "global.h"

extern QSettings settings;

QContentsTreeView::QContentsTreeView(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
    createActions();
    //setAcceptDrops(false);
    //setContextMenuPolicy(Qt::CustomContextMenu );
//    connect(header(),SIGNAL(clicked(QModelIndex)),this,SLOT(headerClicked(QModelIndex)));
}
//void QContentsTreeView::headerClicked(const QModelIndex& index)
//{
//    QModelIndex current = currentIndex();
//    if(index.column()==0){
//        if(current.isValid()){
//            QTreeItem* item = (QTreeItem*)current.internalPointer();
//            QList<QTreeItem*> rows = item->childItemList();
//            qStableSort(rows);
//        }
//    }else if(index.column()==1){
//        if(current.isValid()){
//            QTreeItem* item = (QTreeItem*)current.internalPointer();
//            QList<QTreeItem*> rows = item->childItemList();
//            qStableSort(rows);
//        }
//    }
//}
QContentsTreeView::~QContentsTreeView()
{
    delete menu;
}
void QContentsTreeView::openFile(){
    QModelIndex index = currentIndex();//r(-1), c(-1), p(0), m(0) {}
    emit doubleClicked(index.sibling(index.row(),0));
}
void QContentsTreeView::newFile(){
    dialog.exec();
}
void QContentsTreeView::addExistFile(const QString fileName){
    QTreeItem* item = (QTreeItem*)currentIndex().internalPointer();
    QFileInfo fileInfo(fileName);
    QString project = settings.value(PROJECT_PATH).toString();
    project.append("/");
    project.append(fileInfo.fileName());

    QFile::copy(fileName,project);

    QList<QVariant> columnData;
    columnData<<fileInfo.fileName();
    columnData<<fileInfo.fileName();
    QTreeItem* newItem = new QTreeItem(columnData,item);
    item->appendChild(newItem);
}
void QContentsTreeView::addExistFiles(){
    QStringList fileNames = QFileDialog::getOpenFileNames(0,"Open");
    if(fileNames.isEmpty())
        return;    
    foreach(QString file,fileNames){
        addExistFile(file);
    }
    mainWindow->saveHHC();

    update(rootIndex());
}
void QContentsTreeView::copyFile(){}
void QContentsTreeView::pasteFile()
{
    QClipboard *clipboard = QApplication::clipboard();
    if(clipboard->text()==QString::null)
        return;
    QStringList list(clipboard->text().split("\n"));
    QTreeItem* parent = (QTreeItem*)currentIndex().internalPointer();
    if(parent!=0){
        QList<QTreeItem*> childern = parent->childItemList();
        int min = list.size()<childern.size()?list.size():childern.size();
        for(int i=0;i<min;i++)
        {
            QString da = list.at(i);
            childern.at(i)->setData(currentIndex().column(),da.trimmed());
        }
    }else{
        QTreeItem* parentList = (QTreeItem*)model()->index(0,0).internalPointer();
        QList<QTreeItem*> childern = parentList->childItemList();
        int min = list.size()<childern.size()?list.size():childern.size();
        for(int i=0;i<min;i++)
        {
            QString da = list.at(i);
            childern.at(i)->setData(currentIndex().column(),da.trimmed());
        }
    }
}
void QContentsTreeView::deleteFile()
{
    QModelIndex parent = currentIndex().parent();
//    if(!parent.isValid())
//        return;
    model()->removeRow(currentIndex().row(),parent);
    mainWindow->saveHHC();
    update(rootIndex());
}
void QContentsTreeView::renameFile()
{
    if(!currentIndex().isValid())
        return;
    QTreeItem* renameItem = (QTreeItem*)currentIndex().internalPointer();
    bool ok;
    QString text = QInputDialog::getText(this, tr("Modify Item Name"),
                                         tr("Item name:"), QLineEdit::Normal,
                                         renameItem->data(0).toString(), &ok);
    if (ok && !text.isEmpty())
    {
        renameItem->setData(0,text);
    }
}
void QContentsTreeView::property(){}
void QContentsTreeView::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(tr("Ctrl+P"));
    openAct->setStatusTip(tr("Print the document"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    addExistingAct = new QAction(tr("&Add"), this);
    addExistingAct->setShortcut(tr("Ctrl+A"));
    addExistingAct->setStatusTip(tr("Open an existing file"));
    connect(addExistingAct, SIGNAL(triggered()), this, SLOT(addExistFiles()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcut(tr("Ctrl+C"));
    copyAct->setStatusTip(tr("Save the document to disk"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copyFile()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcut(tr("Ctrl+P"));
    pasteAct->setStatusTip(tr("Print the document"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(pasteFile()));

    deleteAct = new QAction(tr("&Delete"), this);
    deleteAct->setShortcut(tr("Delete"));
    deleteAct->setStatusTip(tr("Print the document"));
    connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteFile()));

    renameAct = new QAction(tr("&Rename"), this);
    renameAct->setShortcut(tr("F2"));
    renameAct->setStatusTip(tr("Print the document"));
    connect(renameAct, SIGNAL(triggered()), this, SLOT(renameFile()));

    moveUpAct = new QAction(tr("&Up"), this);
    moveUpAct->setShortcut(tr("Alt+Up"));
    moveUpAct->setStatusTip(tr("Print the document"));
    connect(moveUpAct, SIGNAL(triggered()), this, SLOT(moveUp()));

    moveDownAct = new QAction(tr("&Down"), this);
    moveDownAct->setShortcut(tr("Alt+Down"));
    moveDownAct->setStatusTip(tr("Print the document"));
    connect(moveDownAct, SIGNAL(triggered()), this, SLOT(moveDown()));

    propertyAct = new QAction(tr("&Properties"), this);
    propertyAct->setShortcut(tr("Alt+Enter"));
    propertyAct->setStatusTip(tr("Properties of File"));
    connect(propertyAct, SIGNAL(triggered()), this, SLOT(property1()));

    menu = new QMenu(this);

    menu->addAction(openAct);
    menu->addSeparator();
    menu->addAction(newAct);
    menu->addAction(addExistingAct);
    menu->addAction(copyAct);
    menu->addAction(pasteAct);
    menu->addSeparator();
    menu->addAction(deleteAct);
    menu->addAction(renameAct);
    menu->addSeparator();
    menu->addAction(moveUpAct);
    menu->addAction(moveDownAct);
    menu->addSeparator();
    menu->addAction(propertyAct);

}
 void QContentsTreeView::moveUp()
 {
    if(!currentIndex().isValid())
        return;

    QModelIndex parentIndex = model()->parent(currentIndex());
    QTreeItem* parentItem = ((QTreeItem*)parentIndex.internalPointer());
    parentItem->moveUp(parentItem->indexOf((QTreeItem*)currentIndex().internalPointer()));
 }
 void QContentsTreeView::moveDown()
 {
    if(!currentIndex().isValid())
        return;
    QModelIndex parentIndex = model()->parent(currentIndex());
    QTreeItem* parentItem = ((QTreeItem*)parentIndex.internalPointer());
    parentItem->moveDown(parentItem->indexOf((QTreeItem*)currentIndex().internalPointer()));

 }
void QContentsTreeView::mouseReleaseEvent(QMouseEvent *event)
{    
    QPoint point = event->globalPos();
    QWidget::mousePressEvent(event);
    if (event->button() == Qt::RightButton)
    {
        setCurrentIndex(indexAt(event->pos()));
        menu->exec(point);
    }
}
//void QContentsTreeView::keyPressEvent(QKeyEvent *e)
//{
//    QTreeView::keyPressEvent(e);
//    if (e->modifiers()==e->key() == Qt::Key_F2)
//    {
//        renameAct->activate(QAction::Trigger);
//    }
//}
//void QContentsTreeView::dragEnterEvent(QDragEnterEvent *event)
// {
//
// }
//
// void QContentsTreeView::dragMoveEvent(QDragMoveEvent *event)
// {
//     event->acceptProposedAction();
// }
//
// void QContentsTreeView::dropEvent(QDropEvent *event)
// {
//     const QMimeData *mimeData = event->mimeData();
//
//     if (mimeData->hasImage()) {
//         //setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
//     } else if (mimeData->hasHtml()) {
//         //setText(mimeData->html());
//         //setTextFormat(Qt::RichText);
//     } else if (mimeData->hasText()) {
//         //setText(mimeData->text());
//         //setTextFormat(Qt::PlainText);
//     } else if (mimeData->hasUrls()) {
//         QList<QUrl> urlList = mimeData->urls();
//         QString text;
//         QTreeItem* item = (QTreeItem*)(currentIndex().internalPointer());
//         for (int i = 0; i < urlList.size() && i < 32; ++i) {
//             QString url = urlList.at(i).path();
//             QList<QVariant> list;
//             list<<"name";
//             list<<url;
//             QTreeItem* newItem = new QTreeItem(list,item);
//             item->appendChild(newItem);
//
//         }
////         setText(text);
//     } else {
//         //setText(tr("Cannot display data"));
//     }
//
//     setBackgroundRole(QPalette::Dark);
//     event->acceptProposedAction();
// }

// void QContentsTreeView::dragLeaveEvent(QDragLeaveEvent *event)
// {
//     clear();
// }

 void QContentsTreeView::clear()
 {
     emit changed();
 }
