#include "qtabeditor.h"

QTabEditor::QTabEditor()
{
    setTabPosition(QTabWidget::North);
    closeButton = new QToolButton();
    closeButton->setIcon(QIcon(":/images/close.png"));
    closeButton->adjustSize();
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeCurrentTab()));
    setCornerWidget(closeButton,Qt::TopRightCorner);
}
void QTabEditor::closeCurrentTab()
{
    removeTab(currentIndex());
}
QTabEditor::~QTabEditor()
{
    foreach(QPlainTextEdit* editor,editorList){
        delete editor;
    }
    foreach(QWebView* browser,browserList){
        delete browser;
    }
    foreach(QTabWidget* widget,tabList){
        delete widget;
    }
    //delete closeButton;
}
int QTabEditor::addTab (const QString& fileName){
    if(list.contains(fileName,Qt::CaseInsensitive)){
        setCurrentIndex(list.indexOf(fileName));
        return 0;
    }
    QString filePath = fileName;
    list.append(filePath);


    QTabWidget* tabWidget = new QTabWidget;
    tabList.append(tabWidget);

/*
    QToolButton *closeTabButton = new QToolButton(this);
    closeTabButton->setEnabled(false);
    closeTabButton->setAutoRaise(true);
    closeTabButton->setToolTip(tr("Close current page"));
    closeTabButton->setIcon(QIcon(QString::fromUtf8(":/trolltech/assistant/images/%1/closetab.png").arg(system)));

    tabWidget->setCornerWidget(closeTabButton, Qt::TopRightCorner);
    connect(closeTabButton, SIGNAL(clicked()), this, SLOT(closeTab()));
*/
    tabWidget->setTabPosition(QTabWidget::South);

    QWebView* browser = new QWebView;
    browserList.append(browser);
    tabWidget->addTab(browser,QIcon(""),"Preview");
    browser->load(QUrl(fileName));

    QPlainTextEdit* editor = new QPlainTextEdit;
    editorList.append(editor);
    tabWidget->addTab(editor,QIcon(""),"Source");

    QFile data(fileName);
    if (data.open(QFile::ReadWrite)) {
        QTextStream out(&data);
        editor->setPlainText(out.readAll());
    }

    int index = QTabWidget::addTab(tabWidget,QIcon(":/images/new.png"),getFileName(filePath));
    this->setCurrentWidget(tabWidget);
    return index;
}
