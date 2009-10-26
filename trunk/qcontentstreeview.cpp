#include "qcontentstreeview.h"
#include "mainwindow.h"
#include "global.h"

extern QSettings settings;

QContentsTreeView::QContentsTreeView(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
    createActions();
    setContextMenuPolicy(Qt::CustomContextMenu);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);

    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showMenu(QPoint)));
    connect(header(),SIGNAL(clicked(QModelIndex)),this,SLOT(showHeaderMenu(QModelIndex)));
}

void QContentsTreeView::showHeaderMenu(QModelIndex i){

}
void QContentsTreeView::keyPressEvent ( QKeyEvent * event )
{
    QAbstractItemView::keyPressEvent ( event );
}
void QContentsTreeView::showMenu(const QPoint& point)
{
    QModelIndex index = indexAt(point);
    if(!index.isValid())
        return;
    //setCurrentIndex(index);
    menu->exec(viewport()->mapToGlobal(point));
}
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

    MainWindow::copy(fileName,project);

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
void QContentsTreeView::copyFile(){
    QClipboard *clipboard = QApplication::clipboard();
    QTreeItem* item = (QTreeItem*)currentIndex().internalPointer();
    if(currentIndex().column()==0){
        clipboard->setText(item->data(0).toString());
    }else if(currentIndex().column()==1){
        clipboard->setText(item->data(1).toString());
    }    
}
void QContentsTreeView::pasteFile()
{
    QClipboard *clipboard = QApplication::clipboard();
    if(clipboard->text()==QString::null)
        return;
    QStringList list(clipboard->text().split("\n"));

    QModelIndexList indexList = selectedIndexes();
    int min = list.size()<indexList.size()?list.size():indexList.size();
    for(int i=0;i<min;i++)
    {
        QString da = list.at(i);
        QModelIndex index = indexList.at(i);
        QTreeItem* item = (QTreeItem*)index.internalPointer();
        item->setData(index.column(),da.trimmed());
    }
}
void QContentsTreeView::deleteFile()
{
    QMessageBox msgBox(QMessageBox::Question, tr("Confirm"),
                       "Are you sure to remove this item?",QMessageBox::Yes | QMessageBox::No);
    if (msgBox.exec() == QMessageBox::No)
        return;

    QModelIndexList indexList = selectedIndexes();
    for(int i=0;i<indexList.size();i++)
    {
        QModelIndex index = indexList.at(i);
        model()->removeRow(index.row(),index.parent());
    }

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
    //QMessageBox::about(0,parentItem->objectName(),"");
    //parentItem->moveUp();
    model()->removeRow(((QTreeItem*)currentIndex().internalPointer())->row(),parentIndex);
 }
 void QContentsTreeView::moveDown()
 {
    if(!currentIndex().isValid())
        return;
    QModelIndex parentIndex = model()->parent(currentIndex());
    QTreeItem* parentItem = ((QTreeItem*)parentIndex.internalPointer());
    parentItem->moveDown(parentItem->indexOf((QTreeItem*)currentIndex().internalPointer()));

 }

 void QContentsTreeView::clear()
 {
     emit changed();
 }
