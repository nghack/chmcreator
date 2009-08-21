#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui>

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class QProjectPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    QProjectPropertiesDialog(QSettings* setting);

public slots:
    void changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    void createIcons();
    QTreeWidgetItem* createItem(QTreeWidgetItem *widget,const QString& title);
    QTreeWidgetItem* createItem(QTreeWidget *widget,const QString& title);

    QTreeWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    QMap<QTreeWidgetItem*,QWidget*> map;
};

#endif
