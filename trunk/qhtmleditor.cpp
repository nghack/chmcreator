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

    QFile file(filename);
    if (!file.open(QFile::ReadOnly)){
        QMessageBox::about(0,tr("Error"),("Can't open file:"+fileName));
        return;
    }

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString content = codec->toUnicode(data);


    document = new QTextDocument(this);
    if (Qt::mightBeRichText(content)) {
        document->setHtml(content);
    }else{
        document->setPlainText(content);
    }

    setTabPosition(QTabWidget::South);

    textEdit = new QTextEdit(this);
    textEdit->setDocument(document);

    editor = new QHTMLSourceEditorCodeEditor(this);
    //editor->setDocument(document);

    highlighter = new Highlighter(editor->document());
    editor->setPlainText(content);
    editor->setWordWrapMode(QTextOption::NoWrap);//editor->setStyleSheet("font-size : 10px");

    browser = new QTextBrowser;//browser->setStyleSheet("font-size : 10px");
    browser->setDocument(document);

    addTab(browser,"Preview");
    addTab(textEdit,"Editor");
    addTab(editor,"Source");

    connect(textEdit->document(),SIGNAL(contentsChanged()),this,SLOT(htmlChanged()));
    connect(editor,SIGNAL(textChanged()),this,SLOT(sourceChanged()));

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

    contentStatus = 0;//
}
void QHTMLEditor::save()
{
    saveAs(filename);
}
void QHTMLEditor::tabChanged(int index)
{
    if(index==2){
        editor->setPlainText(document->toHtml());
    }else{
        document->setHtml(editor->toPlainText());
    }
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
void QHTMLEditor::htmlChanged()
{
    if(contentStatus!=0){
        contentStatus = 0;
        return;
    }
    contentStatus = 1;
    value++;
    QString temp = windowTitle();
    if(ischanged&&value>1&&!temp.endsWith('*')){
        temp+="*";
        setWindowTitle(temp);
    }
//    editor->setPlainText(document->toHtml());
    ischanged = true;
}
void QHTMLEditor::sourceChanged()
{
    if(contentStatus!=0){
        contentStatus = 0;
        return;
    }
    contentStatus = 2;
    value++;
    QString temp = windowTitle();
    if(ischanged&&value>1&&!temp.endsWith('*')){
        temp+="*";
        setWindowTitle(temp);
    }

//    textEdit->setHtml(editor->toPlainText());
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
