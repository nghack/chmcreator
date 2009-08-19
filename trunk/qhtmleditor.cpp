#include "qhtmleditor.h"

QHTMLEditor::~QHTMLEditor(){
    delete browser;
    delete editor;
}
QHTMLEditor::QHTMLEditor(const QString& fileName):filename(fileName)
{
    setTabPosition(QTabWidget::South);

    browser = new QWebView;
    addTab(browser,QIcon(":/images/editor.png"),"Preview");
    browser->load(QUrl(fileName));

    editor = new QPlainTextEdit;
    addTab(editor,QIcon(":/images/source.png"),"Source");

    QFile data(filename);
    if (data.open(QFile::ReadWrite)) {
        QTextStream out(&data);
        editor->setPlainText(out.readAll());
    }
    data.close();
    ischanged = false;

    connect(editor,SIGNAL(textChanged()),this,SLOT(changed()));
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(reload(int)));
//    connect(browser,SIGNAL(linkClicked(QUrl)),this,SLOT(linkClicked(QUrl)));
//    connect(browser,SIGNAL(linkClicked(QUrl)),this,SLOT(linkClick(QUrl)));
}
//void QHTMLEditor::linkClick(QUrl url)
//{
//    browser->load(QUrl(filename));
//    emit linkClicked(url);
//}
void QHTMLEditor::save()
{
    saveAs(filename);
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
    if(index==0){
        if(ischanged){
            QUrl url(filename);
            browser->setHtml(editor->toPlainText(),url.path());
        }else{
            browser->reload();
        }
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
