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
    //editor->setStyleSheet("font-size : 16px");
    data.close();

    highlighter = new Highlighter(editor->document());

    browser = new QTextEdit;
    //browser->setStyleSheet("font-size : 16px");

    browser->setHtml(editor->toPlainText());

    addTab(browser,QIcon(":/images/editor.png"),"HTMLEditor");
    addTab(editor,QIcon(":/images/source.png"),"Source");

    ischanged = true;

    connect(editor,SIGNAL(textChanged()),this,SLOT(changed()));
    connect(browser,SIGNAL(textChanged()),this,SLOT(changed()));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
    ischanged = false;
}
void QHTMLEditor::save()
{
    saveAs(filename);
}
void QHTMLEditor::tabChanged(int index)
{
    if(ischanged)
    {
        if(currentIndex==0)
        {
            browser->setText(editor->toPlainText());
        }
        else
        {
            editor->setPlainText(browser->toHtml());
        }
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
void QHTMLEditor::reload(int index)
{
    /*if(index==0){
        if(ischanged){
            QUrl url(filename);
            browser->setHtml(editor->toPlainText(),url.path());
        }else{
            browser->reload();
        }
    }*/
}
void QHTMLEditor::saveAs(const QString& fileName)
{
    editor->setPlainText(browser->toHtml());
    QFile data(fileName);
    if (data.open(QFile::WriteOnly)) {
        QTextStream out(&data);
        out<<browser->toHtml();
    }
    data.close();
    ischanged = false;
    emit textChanged(false);
}
