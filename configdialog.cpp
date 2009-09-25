#include <QtGui>

#include "configdialog.h"

QProjectPropertiesDialog::QProjectPropertiesDialog(QSettings* setting)
{
    this->setting = setting;
    contentsWidget = new QTreeWidget;
    contentsWidget->header()->hide();

    pagesWidget = new QStackedWidget;

    generalTab = new GeneralTab(setting);
    complierPage = new ComplierPage(setting);
    windowPage = new WindowPage(setting);

    buttonsPage = new ButtonsPage(setting);//Buttons
    positionPage = new PositionPage(setting);//Position
    navPage = new NavPage(setting);//Nav
    stylesPage = new StylesPage(setting);//Styles
    mergePage = new MergePage(setting);

    pagesWidget->addWidget(generalTab);
    pagesWidget->addWidget(complierPage);
    pagesWidget->addWidget(windowPage);

    pagesWidget->addWidget(buttonsPage);//Buttons
    pagesWidget->addWidget(positionPage);//Position
    pagesWidget->addWidget(navPage);//Nav
    pagesWidget->addWidget(stylesPage);//Styles
    pagesWidget->addWidget(mergePage);

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    createIcons();

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(close()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(save()));
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

    map.insert(createItem(configButton,tr("Buttons")),pagesWidget->widget(3));
    map.insert(createItem(configButton,tr("Position")),pagesWidget->widget(4));
    map.insert(createItem(configButton,tr("Navgation Panel")),pagesWidget->widget(5));
    map.insert(createItem(configButton,tr("Styles")),pagesWidget->widget(6));

    map.insert(createItem(contentsWidget,tr("Merge Files")),pagesWidget->widget(7));

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
void QProjectPropertiesDialog::save ()
{
    generalTab->save();
    complierPage->save();
    windowPage->save();

    buttonsPage->save();
    positionPage->save();
    navPage->save();
    stylesPage->save();
    mergePage->save();
}
