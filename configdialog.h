#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui>
#include "pages.h"
#include "qmodifyfiledialog.h"
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
    void save();
private:
    void createIcons();
    QTreeWidgetItem* createItem(QTreeWidgetItem *widget,const QString& title);
    QTreeWidgetItem* createItem(QTreeWidget *widget,const QString& title);

    QTreeWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    QMap<QTreeWidgetItem*,QWidget*> map;
    QSettings* setting;

    GeneralTab* generalTab;
    ComplierPage* complierPage;
    WindowPage* windowPage;

    ButtonsPage* buttonsPage;//Buttons
    PositionPage* positionPage;//Position
    NavPage* navPage;//Nav
    StylesPage* stylesPage;//Styles
    MergePage* mergePage;
};

#endif
