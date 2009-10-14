#ifndef QHTMLEDITOR_H
#define QHTMLEDITOR_H

#include <QtGui>
#include <QWebView>
#include "qhighlighter.h"
#include "qhtmlsourceeditor.h"
#include "helpwindow.h"
class QHTMLEditor : public QTabWidget
{
    Q_OBJECT
public:
    QHTMLEditor(const QString& fileName,QWidget *parent=0);
    ~QHTMLEditor();
    void save();
    void addDir(QString& dirPath,QStringList& list);
    void saveAs(const QString& fileName);
    const QPlainTextEdit* getEditor(){return editor;}
    /*const QWebView* getBrowser(){return browser;}*/
    bool isChanged(){return ischanged;}
    void saveAndClose();
    bool isEditable();
    bool isUndoable(){return isundoable;}
    bool isRedoable(){return isredoable;}
    bool isCopyable(){return iscopyable;}
    bool isCutable(){return iscutable;}
    QPlainTextEdit* textEditor(){return editor;}
    QTextEdit* htmlEditor(){return textEdit;}
    QTextCodec * textCode(){return codec;}
    void load();
    void load(QByteArray encode);
protected:
    void closeEvent(QCloseEvent *e);
signals:
    void textChanged(bool);
    void linkClicked(QUrl);
private slots:
    void tabChanged(int index);
    void htmlChanged();
    void sourceChanged();
    void changeUndo(bool undo){isundoable = undo;}
    void changeRedo(bool redo){isredoable = redo;}
    void changeCopy(bool copy){iscopyable = copy;}
    void changeCut(bool cut){iscutable = cut;}
private:
    bool maybeSave();
    Highlighter* highlighter;
    int currentIndex;
    bool ischanged;
    bool isHTMLChanged;
    bool isSourceChanged;
    int contentStatus;
    QString filename;
    QTextDocument* document;
    QTextBrowser* browser;
    QTextEdit *textEdit;
    QHTMLSourceEditorCodeEditor* editor;
    int value;
    bool iseditable;
    bool isundoable;
    bool isredoable;
    bool iscopyable;
    bool iscutable;
    QTextCodec *codec;
};

#endif // QHTMLEDITOR_H
