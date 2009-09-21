#ifndef QSWITCHWORKSPACEDIALOG_H
#define QSWITCHWORKSPACEDIALOG_H

#include "global.h"
#include <QtGui>

namespace Ui {
    class QSwitchWorkspaceDialog;
}

class QSwitchWorkspaceDialog : public QDialog {
    Q_OBJECT
public:
    QSwitchWorkspaceDialog(QSettings *settings,QWidget *parent = 0);
    ~QSwitchWorkspaceDialog();
    bool isAccepted(){return isaccepted;}
protected:
    void changeEvent(QEvent *e);

private slots:
    void setvalue();
    void selectPath();
private:
    Ui::QSwitchWorkspaceDialog *m_ui;
    QSettings *settings;
    QPushButton* pushbutton;
    QComboBox* comboBox;
    bool isaccepted;
};

#endif // QSWITCHWORKSPACEDIALOG_H
