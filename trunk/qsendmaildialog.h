#ifndef QSENDMAILDIALOG_H
#define QSENDMAILDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QToolButton>
#include "smtp.h"

class QSendMailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QSendMailDialog(QWidget *parent = 0);
    ~QSendMailDialog();

private:
    QLineEdit* subjectLineEdit;
    QTextEdit* contentEdit;

    QToolButton* sendMailButton;
    QToolButton* closeButton;

    QToolButton* promptButton;
    Smtp *mailSender;
private slots:
    void onSendMailTriggered();
    void onSendMailSuccess();
    void onSendMailFailure();
};

#endif // QSENDMAILDIALOG_H
