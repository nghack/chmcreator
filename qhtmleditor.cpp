#include "qhtmleditor.h"

QHTMLEditor::~QHTMLEditor(){
}
QHTMLEditor::QHTMLEditor(const QString& fileName,QWidget *parent):QTabWidget(parent),filename(fileName)
{
    isHTMLChanged = false;
    isSourceChanged = false;
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
    codec = Qt::codecForHtml(data);
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
    QStringList list;
    QString pa = temp.absoluteDir().absolutePath();
    addDir(pa,list);
    browser->setSearchPaths(list);

    browser->setDocument(document);


    addTab(browser,"Preview");
    addTab(textEdit,"Editor");
    addTab(editor,"Source");

    connect(textEdit,SIGNAL(textChanged()),this,SLOT(htmlChanged()));
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

void QHTMLEditor::addDir(QString& dirPath,QStringList& list)
{
    QString dirName = dirPath;
    list<<dirName;

//    QDir dir(dirName);
//    dir.setCurrent(dirName);
//    QStringList listDir = dir.entryList(QDir::Dirs);
//    foreach(QString entry,listDir){
//        if(entry=="."||entry=="..")
//            continue;
//        QString absEntry = dirPath+"/"+entry;
//        list<<absEntry;
//        addDir(absEntry,list);
//    }
}

void QHTMLEditor::save()
{
    saveAs(filename);
}
void QHTMLEditor::tabChanged(int index)
{
    if(index==2&&isHTMLChanged){
        editor->setPlainText(document->toHtml());
    }else if(index==1&&isSourceChanged){
        document->setHtml(editor->toPlainText());
    }
    isHTMLChanged = false;
    isSourceChanged = false;
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
    isHTMLChanged = true;
    value++;
    QString temp = windowTitle();
    if(!temp.endsWith('*')){
        temp+="*";
        setWindowTitle(temp);
    }
    ischanged = true;
}
void QHTMLEditor::sourceChanged()
{
    isSourceChanged = true;
    value++;

    QString temp = windowTitle();
    if(!temp.endsWith('*')){
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
        out.setCodec(codec->name());
        if(isHTMLChanged){
            out<<document->toHtml(codec->name());
        }else{
            out<<editor->toPlainText();
        }
    }
    data.close();
    ischanged = false;
    QFileInfo temp(fileName);
    setWindowTitle(temp.fileName());
}
