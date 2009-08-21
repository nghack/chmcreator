#include "qmodifyfiledialog.h"
#include "ui_qmodifyfiledialog.h"

QModifyFileDialog::QModifyFileDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::QModifyFileDialog)
{
    m_ui->setupUi(this);

    setWindowTitle(tr("Select File"));
    connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(close()));
}

QModifyFileDialog::~QModifyFileDialog()
{
    delete m_ui;
}
void QModifyFileDialog::setModel(QString filePath)
{
    QDirModel* model = new QDirModel;
    m_ui->treeView->setModel(model);
    m_ui->treeView->setRootIndex(model->index(filePath));

    m_ui->treeView->hideColumn(1);
    m_ui->treeView->hideColumn(2);
    m_ui->treeView->hideColumn(3);
}
QString QModifyFileDialog::getSelectFile(QString defaultValue){
    QModelIndex index = m_ui->treeView->currentIndex();
    if(!index.isValid()) return defaultValue;
    QString result = index.data(Qt::DisplayRole).toString();

    QModelIndex parentIndex = index.parent();
    while(parentIndex!=m_ui->treeView->rootIndex()){
        result = parentIndex.data(Qt::DisplayRole).toString()+"/"+result;
        parentIndex = parentIndex.parent();
    }
    return result;
}
void QModifyFileDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
