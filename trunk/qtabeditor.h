#ifndef QTABEDITOR_H
#define QTABEDITOR_H

#include <QtGui>
#include <QWebView>
#include <QTabWidget>

class QTabEditor : public QTabWidget
{
    Q_OBJECT
public:
    QTabEditor();
    ~QTabEditor();
    int addTab (const QString& fileName);
private:
    QString getFileName(const QString& fileName){
        name = fileName;
        return name.right(name.length()-name.lastIndexOf('/')-1);
    }
    QString name;
    QStringList list;
    QVector<QTabWidget*> tabList;
    QVector<QPlainTextEdit*> editorList;
    QVector<QWebView*> browserList;

    QToolButton* closeButton;
private slots:
    void closeCurrentTab();
};

#endif // QTABEDITOR_H
