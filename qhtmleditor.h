#ifndef QHTMLEDITOR_H
#define QHTMLEDITOR_H

#include <QtGui>
#include <QWebView>
#include "qhighlighter.h"
class QHTMLEditor : public QTabWidget
{
    Q_OBJECT
public:
    QHTMLEditor(const QString& fileName);
    ~QHTMLEditor();
    void save();
    void saveAs(const QString& fileName);
    const QPlainTextEdit* getEditor(){return editor;}
    /*const QWebView* getBrowser(){return browser;}*/
    bool isChanged(){return ischanged;}
signals:
    void textChanged(bool);
    void linkClicked(QUrl);
private slots:
    void tabChanged(int index);
    void changed();
    void reload(int);
//    void linkClick(QUrl);

private:
    Highlighter* highlighter;
    int currentIndex;
    bool ischanged;
    QString filename;
    QTextDocument* document;
    QTextEdit* browser;
    QPlainTextEdit* editor;
};

#endif // QHTMLEDITOR_H
