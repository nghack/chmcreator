#include "qhtmleditor.h"

QHTMLEditor::~QHTMLEditor(){
    /*delete browser;*/
    delete editor;
}
QHTMLEditor::QHTMLEditor(const QString& fileName):filename(fileName)
{
    ischanged = false;
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

    connect(editor,SIGNAL(textChanged()),this,SLOT(changed()));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
    ischanged = false;
    value = 0;
}
void QHTMLEditor::save()
{
    saveAs(filename);
}
void QHTMLEditor::tabChanged(int index)
{
    if(index==0&&ischanged)browser->setText(editor->toPlainText());
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
