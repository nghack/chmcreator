#include <QtGui>

#include "configdialog.h"
#include "pages.h"

QProjectPropertiesDialog::QProjectPropertiesDialog(QSettings* setting)
{
    contentsWidget = new QTreeWidget;
    contentsWidget->header()->hide();

    QFileInfo fileInfo(".");
    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new GeneralTab(setting));
    pagesWidget->addWidget(new UpdatePage);
    pagesWidget->addWidget(new QueryPage);
    pagesWidget->addWidget(new ConfigurationPage);
    pagesWidget->addWidget(new FilesTab(fileInfo));
    pagesWidget->addWidget(new ComplierTab(fileInfo));
    pagesWidget->addWidget(new WindowTab(fileInfo));

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    createIcons();

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(close()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(buttonBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    //    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));
}
QTreeWidgetItem* QProjectPropertiesDialog::createItem(QTreeWidgetItem *widget,const QString& title)
{
    QTreeWidgetItem *configButton = new QTreeWidgetItem(widget);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    configButton->setText(0,title);
    return configButton;
}
QTreeWidgetItem* QProjectPropertiesDialog::createItem(QTreeWidget *widget,const QString& title)
{
    QTreeWidgetItem *configButton = new QTreeWidgetItem(widget);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    configButton->setText(0,title);
    return configButton;
}
void QProjectPropertiesDialog::createIcons()
{
    map.insert(createItem(contentsWidget,tr("General")),pagesWidget->widget(0));
    map.insert(createItem(contentsWidget,tr("Compiler")),pagesWidget->widget(1));

    QTreeWidgetItem *configButton = createItem(contentsWidget,tr("Windows Types"));
    map.insert(configButton,pagesWidget->widget(2));

    map.insert(createItem(configButton,tr("General")),pagesWidget->widget(3));
    map.insert(createItem(configButton,tr("General")),pagesWidget->widget(4));
    map.insert(createItem(configButton,tr("General")),pagesWidget->widget(5));

    map.insert(createItem(contentsWidget,tr("Merge Files")),pagesWidget->widget(6));

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
            this, SLOT(changePage(QTreeWidgetItem *, QTreeWidgetItem*)));
}

void QProjectPropertiesDialog::changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (!current)
        current = previous;
    pagesWidget->setCurrentWidget(map.value(current));
}
void QProjectPropertiesDialog::accept ()
{
    QDialog::accept();
}
void QProjectPropertiesDialog::reject ()
{
    QDialog::reject();
}
