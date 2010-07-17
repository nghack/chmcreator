#include "qsendmaildialog.h"

QSendMailDialog::QSendMailDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel(tr("<b>To:</b>")),0,0,1,1,Qt::AlignRight);
    layout->addWidget(new QLabel("chmcreator"),0,1,1,1);

    layout->addWidget(new QLabel(tr("<b>Subject:</b>")),1,0,1,1,Qt::AlignRight);
    subjectLineEdit = new QLineEdit();
    layout->addWidget(subjectLineEdit,1,1,1,1);

    layout->addWidget(new QLabel(tr("<b>Content:</b>")),2,0,1,1,Qt::AlignTop);
    contentEdit = new QTextEdit();
    layout->addWidget(contentEdit,2,1,1,1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    sendMailButton = new QPushButton(tr("Send Mail"));
    hlayout->addWidget(sendMailButton);
    closeButton = new QPushButton(tr("Close"));
    hlayout->addWidget(closeButton);
    hlayout->addWidget(new QLabel(""));
    hlayout->setStretch(3,10);

    promptLabel = new QLabel("");
    layout->addWidget(promptLabel,3,0,1,1);
    layout->addLayout(hlayout,3,1,1,1);

    layout->setColumnStretch(1, 10);
    mainLayout->addLayout(layout);

    setLayout(mainLayout);
    setMaximumSize(600,400);
    setMinimumSize(600,400);

    connect(sendMailButton,SIGNAL(clicked()),this,SLOT(onSendMailTriggered()));

    mailSender = new Smtp("smtp.163.com","zrx285@163.com","141246883");
    connect(mailSender,SIGNAL(status(QString)),this,SLOT(onSendMailStatus(QString)));
    connect(mailSender,SIGNAL(successQuit()),this,SLOT(onSendMailSuccess()));
    connect(mailSender,SIGNAL(errorCloseAll()),this,SLOT(onSendMailFailure()));
}

QSendMailDialog::~QSendMailDialog()
{
}
void QSendMailDialog::onSendMailTriggered(){
    promptLabel->setText("starting");
    mailSender->send("zrx285@163.com","zrx285@163.com",subjectLineEdit->text(),contentEdit->toPlainText());
    promptLabel->setText("send end");
}
void QSendMailDialog::onSendMailStatus(QString status){
    promptLabel->setText(status);
}
void QSendMailDialog::onSendMailSuccess(){
    promptLabel->setText("Success!");
}
void QSendMailDialog::onSendMailFailure(){
    promptLabel->setText("Failure!");
}
