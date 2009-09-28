#include "qhtmleditor.h"

QHTMLEditor::~QHTMLEditor(){
}
QHTMLEditor::QHTMLEditor(const QString& fileName,QWidget *parent):QTabWidget(parent),filename(fileName)
{
    filename = fileName;
    ischanged = true;
    QFileInfo temp(fileName);
    setWindowTitle(temp.fileName());
    setWindowIcon(QIcon(":/images/new.png"));
    currentIndex = indexOf(currentWidget());
    QFile data(filename);

    if (!data.open(QFile::ReadWrite)) {
        QMessageBox::about(0,tr("Error"),("Can't open file:"+fileName));
        return;
    }
    QTextStream stream(&data);

    setTabPosition(QTabWidget::South);

    editor = new QHTMLSourceEditorCodeEditor(this);

    editor->setPlainText(stream.readAll());
    editor->setWordWrapMode(QTextOption::NoWrap);
    //editor->setStyleSheet("font-size : 10px");
    data.close();

    highlighter = new Highlighter(editor->document());

    browser = new QTextBrowser;
    //browser->setStyleSheet("font-size : 10px");
    browser->setHtml(editor->toPlainText());

    addTab(browser,QIcon(":/images/editor.png"),"Preview");
    addTab(editor,QIcon(":/images/source.png"),"Source");

    connect(editor,SIGNAL(textChanged()),this,SLOT(changed()));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));

    ischanged = false;
    value = 0;
    iseditable = false;

    isundoable = false;
    isredoable = false;
    iscopyable = false;
    iscutable = false;
    connect(editor,SIGNAL(undoAvailable(bool)),this,SLOT(changeRedo(bool)));
    connect(editor,SIGNAL(redoAvailable(bool)),this,SLOT(changeRedo(bool)));
    connect(editor,SIGNAL(copyAvailable(bool)),this,SLOT(changeCopy(bool)));
    connect(editor,SIGNAL(copyAvailable(bool)),this,SLOT(changeCut(bool)));
}
void QHTMLEditor::save()
{
    saveAs(filename);
}
void QHTMLEditor::tabChanged(int index)
{
    if(index==0&&ischanged)browser->setText(editor->toPlainText());
    if(index==1)iseditable = true;

}
bool QHTMLEditor::isEditable(){
    return iseditable;
}
void QHTMLEditor::saveAndClose()
{
    if(!ischanged)
        return;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0,tr("Confirm"),tr("File has changed, save file?"),QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
       return;
    save();
}
void QHTMLEditor::changed()
{
    value++;
    QString temp = windowTitle();
    if(ischanged&&value>1&&!temp.endsWith('*')){
        temp+="*";
        setWindowTitle(temp);
    }
    ischanged = true;
}
void QHTMLEditor::saveAs(const QString& fileName)
{
    QFile data(fileName);
    if (data.open(QFile::WriteOnly)) {
        QTextStream out(&data);
        out<<editor->toPlainText();
    }
    data.close();
    ischanged = false;
    QFileInfo temp(fileName);
    setWindowTitle(temp.fileName());
}
