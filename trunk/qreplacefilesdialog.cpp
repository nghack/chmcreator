#include <QtGui>

#include "qreplacefilesdialog.h"


QReplaceFilesDialog::QReplaceFilesDialog(const QString& sedPath,QWidget *parent)
    : QDialog(parent)
{
    if(sedPath==QString::null){
       this->sedPath = QDir::currentPath();
   }else{
       this->sedPath = sedPath;
   }
    findTextLabel = new QLabel(tr("Find Text:"));
    findTextComboBox = createComboBox(tr(""));
    replaceButton = createButton(tr("&Replace All"), SLOT(replace()));

    replaceTextLabel = new QLabel(tr("Replace With Text:"));
    replaceTextComboBox = createComboBox();
    closeButton = createButton(tr("&Close"), SLOT(close()));

    typeTextLabel = new QLabel(tr("File Type:"));
    typeComboBox = createComboBox("*");
    typeButton = createButton(tr("&Refresh File List"), SLOT(find()));

    directoryLabel = new QLabel(tr("In Directory:"));
    directoryComboBox = createComboBox();
    directoryBrowseButton = createButton(tr("&Browse..."), SLOT(browse()));

    createFilesTable();

    replaceBottomButton = createButton(tr("&Replace All"), SLOT(replace()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(findTextLabel, 0, 0);
    mainLayout->addWidget(findTextComboBox, 0, 1);
    mainLayout->addWidget(replaceButton, 0, 2);

    mainLayout->addWidget(replaceTextLabel, 1, 0);
    mainLayout->addWidget(replaceTextComboBox, 1, 1);
    mainLayout->addWidget(closeButton, 1, 2);

    mainLayout->addWidget(typeTextLabel, 2, 0);
    mainLayout->addWidget(typeComboBox, 2, 1);
    //mainLayout->addWidget(typeButton, 2, 2);

    mainLayout->addWidget(directoryLabel, 3, 0);
    mainLayout->addWidget(directoryComboBox, 3, 1);
    mainLayout->addWidget(directoryBrowseButton, 3, 2);

    mainLayout->addWidget(filesTable, 4, 0,1,3);
    mainLayout->addWidget(typeButton, 5, 0);
    mainLayout->addWidget(replaceBottomButton, 5, 2);

    setLayout(mainLayout);

    setWindowTitle(tr("Replace In Files"));
    resize(700, 300);
}
//! [1]
void QReplaceFilesDialog::setInitualValue(const QString& path,const QString findText,const QString& replaceText,const QString& fileType)
{
    findTextComboBox->setEditText(findText);
    replaceTextComboBox->setEditText(replaceText);
    typeComboBox->setEditText(fileType);
    directoryComboBox->setEditText(path);
}
//! [2]
void QReplaceFilesDialog::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Find Files"), directoryComboBox->currentText());
    if (!directory.isEmpty()) {
        directoryComboBox->addItem(directory);
        directoryComboBox->setCurrentIndex(directoryComboBox->currentIndex() + 1);
    }
}
//! [2]
void QReplaceFilesDialog::replace()
{
    filesTable->setRowCount(0);

    QString findText = findTextComboBox->currentText();
    QString replaceText = replaceTextComboBox->currentText();
    QString fileType = typeComboBox->currentText();
    QString path = directoryComboBox->currentText();

    QDir directory = QDir(path);
    QStringList files;
    if (fileType.isEmpty())
        fileType = "*";
    files = directory.entryList(QStringList(fileType),
                                QDir::Files | QDir::NoSymLinks | QDir::AllDirs);

    if (!findText.isEmpty())
        files = replaceFiles(directory, files, findText);
    showFiles(directory, files);

}

void QReplaceFilesDialog::find()
{
    filesTable->setRowCount(0);

    QString findText = findTextComboBox->currentText();
    QString replaceText = replaceTextComboBox->currentText();
    QString fileType = typeComboBox->currentText();
    QString path = directoryComboBox->currentText();

    QDir directory = QDir(path);
    QStringList files;
    if (fileType.isEmpty())
        fileType = "*";
    files = directory.entryList(QStringList(fileType),
                                QDir::Files | QDir::NoSymLinks | QDir::AllDirs);

    if (!findText.isEmpty())
        files = findFiles(directory, files, findText);
    showFiles(directory, files);
}

QStringList QReplaceFilesDialog::findFiles(const QDir &directory, const QStringList &files,
                              const QString &text)
{
    QProgressDialog progressDialog(this);
    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Find Files"));

//! [5] //! [6]
    QStringList foundFiles;

    for (int i = 0; i < files.size(); ++i) {
        progressDialog.setValue(i);
        progressDialog.setLabelText(tr("Searching file number %1 of %2...")
                                    .arg(i).arg(files.size()));
        qApp->processEvents();
//! [6]

        if (progressDialog.wasCanceled())
            break;

//! [7]
        QFile file(directory.absoluteFilePath(files[i]));

        if (file.open(QIODevice::ReadOnly)) {
            QString line;
            QTextStream in(&file);
            while (!in.atEnd()) {
                if (progressDialog.wasCanceled())
                    break;
                line = in.readLine();
                if (line.contains(text)) {
                    foundFiles << files[i];
                    break;
                }
            }
        }
    }
    return foundFiles;
}
QStringList QReplaceFilesDialog::replaceFiles(const QDir &directory, const QStringList &files,
                                           const QString &text)
{
    QProgressDialog progressDialog(this);
    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Find Files"));

    //! [5] //! [6]
    QStringList foundFiles;

    QString findText = findTextComboBox->currentText();
    QString replaceText = replaceTextComboBox->currentText();
    for (int i = 0; i < files.size(); ++i) {
        progressDialog.setValue(i);
        progressDialog.setLabelText(tr("Replacing file number %1 of %2...")
                                    .arg(i).arg(files.size()));
        qApp->processEvents();
        //! [6]

        if (progressDialog.wasCanceled())
            break;

        bool isReplace = false;
        QFile file(directory.absoluteFilePath(files[i]));
        QTemporaryFile tempfile;

        if (file.open(QIODevice::ReadOnly)&&tempfile.open()) {
            QTextStream in(&file);
            QTextStream out(&tempfile);
            QString line;
            while (!in.atEnd()) {
                if (progressDialog.wasCanceled())
                    break;
                line = in.readLine();
                if (line.contains(text)) {
                    if(!isReplace){
                        isReplace = true;
                        foundFiles << files[i];
                    }
                    line.replace(findText,replaceText);
                }
                line.append("\n");
                out<<line;
            }
            file.close();
            tempfile.close();
        }
        if(isReplace){
            if(file.open(QIODevice::WriteOnly)&&tempfile.open()){
                QTextStream out(&file);
                QTextStream in(&tempfile);
                while (!in.atEnd()) {
                    out<<in.readLine();
                    out<<"\n";
                }
                file.close();
                tempfile.close();
            }
        }
    }
    return foundFiles;
}
//! [7]

//! [8]
void QReplaceFilesDialog::showFiles(const QDir &directory, const QStringList &files)
{
    for (int i = 0; i < files.size(); ++i) {
        QFile file(directory.absoluteFilePath(files[i]));
        qint64 size = QFileInfo(file).size();

        QTableWidgetItem *fileNameItem = new QTableWidgetItem(files[i]);
        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *sizeItem = new QTableWidgetItem(tr("%1 KB")
                                             .arg(int((size + 1023) / 1024)));
        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);
        filesTable->setItem(row, 1, sizeItem);
    }
//    filesFoundLabel->setText(tr("%1 file(s) found").arg(files.size()) +
//                             (" (Double click on a file to open it)"));
}
//! [8]

//! [9]
QPushButton *QReplaceFilesDialog::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
//! [9]

//! [10]
QComboBox *QReplaceFilesDialog::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}
//! [10]

//! [11]
void QReplaceFilesDialog::createFilesTable()
{
    filesTable = new QTableWidget(0, 2);
    filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList labels;
    labels << tr("File Name") << tr("Size");
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    filesTable->verticalHeader()->hide();
    filesTable->setShowGrid(false);

    connect(filesTable, SIGNAL(cellActivated(int, int)),
            this, SLOT(openFileOfItem(int, int)));
}
//! [11]

//! [12]

void QReplaceFilesDialog::openFileOfItem(int row, int /* column */)
{
    QTableWidgetItem *item = filesTable->item(row, 0);
    QDesktopServices::openUrl(item->text());
}

//! [12]

