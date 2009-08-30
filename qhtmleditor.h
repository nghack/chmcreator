#ifndef QHTMLEDITOR_H
#define QHTMLEDITOR_H

#include <QtGui>
#include <QWebView>

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
    void changed();
    void reload(int);
//    void linkClick(QUrl);

private:
    bool ischanged;
    QString filename;
    /*QWebView* browser;*/
    QPlainTextEdit* editor;
};

#endif // QHTMLEDITOR_H
