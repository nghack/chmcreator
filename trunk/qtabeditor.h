#ifndef QTABEDITOR_H
#define QTABEDITOR_H

#include <QtGui>
#include <QWebView>
#include <QTabWidget>
#include "qhtmleditor.h"

class QTabEditor : public QTabWidget
{
    Q_OBJECT
public:
    QTabEditor();
    ~QTabEditor();
    int addTab (const QString& fileName);
    void save();
    void saveAll();
public slots:
    void changeStatus(bool);
private:
    QString getFileName(const QString& fileName){
        name = fileName;
        return name.right(name.length()-name.lastIndexOf('/')-1);
    }
    QString name;
    QStringList list;
    QVector<QHTMLEditor*> tabList;
    QToolButton* closeButton;
private slots:
    void closeCurrentTab();
};

#endif // QTABEDITOR_H
