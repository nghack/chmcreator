#ifndef QReplaceFilesDialog_H
#define QReplaceFilesDialog_H

#include <QDialog>
#include <QProcess>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDir;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE

//! [0]
class QReplaceFilesDialog : public QDialog
{
    Q_OBJECT

public:
    QReplaceFilesDialog(const QString& sedPath,QWidget *parent = 0);
    void setInitualValue(const QString& path,const QString findText,const QString& replaceText,const QString& fileType);

private slots:
    void browse();
    void find();
    void replace();
    void openFileOfItem(int row, int column);

private:
    QStringList replaceFiles(const QDir &directory, const QStringList &files,
                                           const QString &text);
    QStringList findFiles(const QDir &directory, const QStringList &files,
                          const QString &text);
    void showFiles(const QDir &directory, const QStringList &files);
    QPushButton *createButton(const QString &text, const char *member);
    QComboBox *createComboBox(const QString &text = QString());
    void createFilesTable();

    QLabel *findTextLabel;
    QComboBox *findTextComboBox;
    QPushButton *replaceButton;

    QLabel *replaceTextLabel;
    QComboBox *replaceTextComboBox;
    QPushButton *closeButton;

    QLabel *typeTextLabel;
    QComboBox *typeComboBox;
    QPushButton *typeButton;

    QLabel *directoryLabel;
    QComboBox *directoryComboBox;
    QPushButton *directoryBrowseButton;

    QLabel *filesFoundLabel;
    QPushButton *replaceBottomButton;
    QTableWidget *filesTable;
    QProcess* replaceProcess;

    QString sedPath;
};

#endif
