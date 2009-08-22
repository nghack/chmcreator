#include "newfiledialog.h"
#include "ui_newfiledialog.h"

NewFileDialog::NewFileDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::NewFileDialog)
{
    m_ui->setupUi(this);

    QLabel *nameLabel = new QLabel(tr("Title Name:"));
    QLineEdit *nameLineEdit = new QLineEdit;

    QLabel *emailLabel = new QLabel(tr("File Name:"));
    QLineEdit *emailLineEdit = new QLineEdit;

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    layout->addWidget(buttonBox, 2,0,1,2);

    setLayout(layout);
}

NewFileDialog::~NewFileDialog()
{
    delete m_ui;
}

void NewFileDialog::changeEvent(QEvent *e)
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
