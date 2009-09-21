#ifndef QHTMLEDITOR_H
#define QHTMLEDITOR_H

#include <QtGui>
#include <QWebView>
#include "qhighlighter.h"
#include "qhtmlsourceeditor.h"
class QHTMLEditor : public QTabWidget
{
    Q_OBJECT
public:
    QHTMLEditor(const QString& fileName,QWidget *parent=0);
    ~QHTMLEditor();
    void save();
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
signals:
    void textChanged(bool);
    void linkClicked(QUrl);
private slots:
    void tabChanged(int index);
    void changed();
    void changeUndo(bool undo){isundoable = undo;}
    void changeRedo(bool redo){isredoable = redo;}
    void changeCopy(bool copy){iscopyable = copy;}
    void changeCut(bool cut){iscutable = cut;}


private:
    Highlighter* highlighter;
    int currentIndex;
    bool ischanged;
    QString filename;
    QTextDocument* document;
    QTextBrowser* browser;
    QHTMLSourceEditorCodeEditor* editor;
    int value;
    bool iseditable;
    bool isundoable;
    bool isredoable;
    bool iscopyable;
    bool iscutable;
};

#endif // QHTMLEDITOR_H
