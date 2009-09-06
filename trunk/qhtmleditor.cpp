#include "qhtmleditor.h"

QHTMLEditor::~QHTMLEditor(){
    /*delete browser;*/
    delete editor;
}
QHTMLEditor::QHTMLEditor(const QString& fileName):filename(fileName)
{
    currentIndex = indexOf(currentWidget());
    QFile data(filename);

    if (!data.open(QFile::ReadWrite)) {
        QMessageBox::about(0,tr("Error"),("Can't open file:"+fileName));
        return;
    }
    QTextStream stream(&data);

    setTabPosition(QTabWidget::South);

    editor = new QPlainTextEdit;

    editor->setPlainText(stream.readAll());
    editor->setStyleSheet("font-size : 16px");
    data.close();

    highlighter = new Highlighter(editor->document());

    browser = new QTextBrowser;
    browser->setStyleSheet("font-size : 16px");
    browser->setHtml(editor->toPlainText());

    addTab(browser,QIcon(":/images/editor.png"),"HTMLEditor");
    addTab(editor,QIcon(":/images/source.png"),"Source");

    ischanged = false;

    connect(editor,SIGNAL(textChanged()),this,SLOT(changed()));
    //connect(browser,SIGNAL(textChanged()),this,SLOT(changed()));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
}
void QHTMLEditor::save()
{
    saveAs(filename);
}
void QHTMLEditor::tabChanged(int index)
{
    if(ischanged&&index==0)
    {
        browser->setText(editor->toPlainText());
    }
    currentIndex = index;
}
void QHTMLEditor::changed()
{
    if(!ischanged){
        ischanged = true;
        emit textChanged(true);
    }
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
    emit textChanged(false);
}
