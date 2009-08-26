#ifndef QMODIFYFILEDIALOG_H
#define QMODIFYFILEDIALOG_H

#include <QtGui>

namespace Ui {
    class QModifyFileDialog;
}

class QModifyFileDialog : public QDialog {
    Q_OBJECT
public:
    QModifyFileDialog(QWidget *parent = 0);
    ~QModifyFileDialog();
    void setModel(QString filePath);
    QString getSelectFile(QString defaultValue=QString::null);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::QModifyFileDialog *m_ui;
};

#endif // QMODIFYFILEDIALOG_H
