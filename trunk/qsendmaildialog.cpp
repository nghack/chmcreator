#include "qsendmaildialog.h"

QSendMailDialog::QSendMailDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel(tr("<b>To:</b>")),0,0,1,1,Qt::AlignRight);
    layout->addWidget(new QLabel("chmcreator"),0,1,1,1);

    layout->addWidget(new QLabel(tr("<b>Subject:</b>")),1,0,1,1,Qt::AlignRight);
    subjectLineEdit = new QLineEdit(tr("CHMCreator Suggestion"));
    subjectLineEdit->setEnabled(false);
    layout->addWidget(subjectLineEdit,1,1,1,1);

    layout->addWidget(new QLabel(tr("<b>Content:</b>")),2,0,1,1,Qt::AlignTop);
    contentEdit = new QTextEdit();
    layout->addWidget(contentEdit,2,1,1,1);

    QHBoxLayout *hlayout = new QHBoxLayout;

    sendMailButton = new QToolButton();
    sendMailButton->setText(tr("Send Mail"));
    hlayout->addWidget(sendMailButton);
    closeButton = new QToolButton();
    closeButton->setText(tr("Close"));
    hlayout->addWidget(closeButton);

    sendMailButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    closeButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //hlayout->addWidget(promptButton);
    hlayout->addWidget(new QLabel(""));
    hlayout->setStretch(4,10);

    layout->addLayout(hlayout,3,1,1,1);

    layout->setColumnStretch(1, 10);
    mainLayout->addLayout(layout);

    setLayout(mainLayout);
    setMaximumSize(600,400);
    setMinimumSize(600,400);

    connect(sendMailButton,SIGNAL(clicked()),this,SLOT(onSendMailTriggered()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    mailSender = new Smtp("smtp.163.com","chmcreator@163.com","");

    connect(mailSender,SIGNAL(successQuit()),this,SLOT(onSendMailSuccess()));
    connect(mailSender,SIGNAL(errorCloseAll()),this,SLOT(onSendMailFailure()));
}

QSendMailDialog::~QSendMailDialog()
{
}
void QSendMailDialog::onSendMailTriggered(){
    QIcon icon = QIcon(":/images/loading.png");
    //sendMailButton->setIcon(icon);
    sendMailButton->setText(tr("Sending..."));
    mailSender->send("chmcreator@163.com","chmcreator@163.com",subjectLineEdit->text(),contentEdit->toPlainText());
}
void QSendMailDialog::onSendMailSuccess(){
    QIcon icon = QIcon(":/images/success.png");
    //sendMailButton->setIcon(icon);
    sendMailButton->setText(tr("Send Sucess!"));
    sendMailButton->setEnabled(false);
}
void QSendMailDialog::onSendMailFailure(){
    QIcon icon = QIcon(":/images/failure.png");
    //sendMailButton->setIcon(icon);
    sendMailButton->setText(tr("Send Failure!"));
    sendMailButton->setEnabled(false);
}
