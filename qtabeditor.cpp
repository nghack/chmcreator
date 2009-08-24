#include "qtabeditor.h"

QTabEditor::QTabEditor()
{
    setTabPosition(QTabWidget::North);

    closeButton = new QToolButton();
    closeButton->setIcon(QIcon(":/images/close.png"));
    closeButton->adjustSize();
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeCurrentTab()));
    setCornerWidget(closeButton,Qt::TopRightCorner);
}
void QTabEditor::closeCurrentTab()
{
    int index = currentIndex();
    list.removeAt(index);
    tabList.remove(index);
    removeTab(index);
    if(tabList.count()==0){
        QMdiArea* area = (QMdiArea*)parent();

    }
}
QTabEditor::~QTabEditor()
{
    foreach(QHTMLEditor* editor,tabList){
        delete editor;
    }
    delete closeButton;
}
int QTabEditor::addTab (const QString& fileName){
    if(list.contains(fileName,Qt::CaseInsensitive)){
        setCurrentIndex(list.indexOf(fileName));
        return 0;
    }
    QString filePath = fileName;
    list.append(filePath);


    QHTMLEditor* tabWidget = new QHTMLEditor(filePath);
    tabList.append(tabWidget);

    connect(tabWidget, SIGNAL(textChanged(bool)), this, SLOT(changeStatus(bool)));

    int index = QTabWidget::addTab(tabWidget,QIcon(":/images/new.png"),getFileName(filePath));
    this->setCurrentWidget(tabWidget);
    return index;
}
void QTabEditor::changeStatus(bool isChanged)
{
    int index = currentIndex();
    if(index<0)
        return;
    QString text = tabText(index);
    if(isChanged){
        if(!text.endsWith('*'))
            setTabText(index,text+"*");
    }else{
        if(text.endsWith('*'))
            setTabText(index,text.left(text.length()-1));
    }
}
void QTabEditor::save()
{
    QHTMLEditor* editor = (QHTMLEditor*)this->currentWidget();
    if(editor!=0&&editor->isChanged())editor->save();
}
void QTabEditor::saveAll()
{
}
