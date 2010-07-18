#include "newfiledialog.h"
#include "ui_newfiledialog.h"

NewFileDialog::NewFileDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::NewFileDialog)
{
    m_ui->setupUi(this);

    this->setWindowTitle("New File");
    QLabel *nameLabel = new QLabel(tr("Title Name:"));
    titleLineEdit = new QLineEdit;

    QLabel *emailLabel = new QLabel(tr("File Name:"));
    fileNameLineEdit = new QLineEdit;

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    connect(buttonBox,SIGNAL(accepted()),this,SLOT(createItem()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(close()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(titleLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(fileNameLineEdit, 1, 1);
    layout->addWidget(buttonBox, 2,0,1,2);

    setLayout(layout);
}

NewFileDialog::~NewFileDialog()
{
    delete m_ui;
}

void NewFileDialog::createItem(){
    emit onCreateItem(titleLineEdit->text(),fileNameLineEdit->text());
    this->close();
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
