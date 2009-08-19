#include "qmodifyfiledialog.h"
#include "ui_qmodifyfiledialog.h"

QModifyFileDialog::QModifyFileDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::QModifyFileDialog)
{
    m_ui->setupUi(this);

    setWindowTitle(tr("Select File"));
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
