#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

//! [0]
class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *fromStartCheckBox;
    QCheckBox *wholeWordsCheckBox;
    QCheckBox *searchSelectionCheckBox;
    QCheckBox *backwardCheckBox;
    QDialogButtonBox *buttonBox;
    QPushButton *findButton;
    QPushButton *moreButton;
    QWidget *extension;
};
//! [0]

#endif
