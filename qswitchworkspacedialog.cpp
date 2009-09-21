#include "qswitchworkspacedialog.h"
#include "ui_qswitchworkspacedialog.h"

class QWizardHeader : public QWidget
{
public:
    enum RulerType { Ruler };

    inline QWizardHeader(RulerType /* ruler */, QWidget *parent = 0)
        : QWidget(parent) { setFixedHeight(2); }
    QWizardHeader(QWidget *parent = 0);

    void setup(const QString &title,
               const QString &subTitle);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QLabel *titleLabel;
    QLabel *subTitleLabel;
    QLabel *logoLabel;
    QGridLayout *layout;
    QPixmap bannerPixmap;
};

QWizardHeader::QWizardHeader(QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setBackgroundRole(QPalette::Base);

    titleLabel = new QLabel(this);
    titleLabel->setBackgroundRole(QPalette::Base);

    subTitleLabel = new QLabel(this);
    subTitleLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    subTitleLabel->setWordWrap(true);

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(Qt::white));

    titleLabel->setPalette(palette);
    titleLabel->setAutoFillBackground(true);

    subTitleLabel->setPalette(palette);
    subTitleLabel->setAutoFillBackground(true);

    setPalette(palette);
    setAutoFillBackground(true);

    logoLabel = new QLabel(this);

    QFont font = titleLabel->font();
    font.setBold(true);
    titleLabel->setFont(font);

    layout = new QGridLayout(this);
    layout->setMargin(5);
    layout->setSpacing(3);

    layout->setRowMinimumHeight(3, 1);
    layout->setRowStretch(4, 1);

    layout->setColumnStretch(2, 1);
    layout->setColumnMinimumWidth(4, 0);
    layout->setColumnMinimumWidth(6, 0);

    layout->addWidget(titleLabel, 2, 1, 1, 2);
    layout->addWidget(subTitleLabel, 4, 2);
    layout->addWidget(logoLabel, 1, 5, 5, 1);
}

void QWizardHeader::setup(const QString &title,
               const QString &subTitle)
{
    layout->setRowMinimumHeight(0, 0);
    layout->setRowMinimumHeight(1, 0);
    layout->setRowMinimumHeight(6, 5);

    int minColumnWidth0 = 0;
    int minColumnWidth1 = 5;
    layout->setColumnMinimumWidth(0, minColumnWidth0);
    layout->setColumnMinimumWidth(1, minColumnWidth1);

    titleLabel->setTextFormat(Qt::AutoText);
    titleLabel->setText(title);

    subTitleLabel->setTextFormat(Qt::AutoText);
    subTitleLabel->setText(QLatin1String("Pq\nPq"));
    int desiredSubTitleHeight = subTitleLabel->sizeHint().height();
    subTitleLabel->setText(subTitle);

    bannerPixmap = QPixmap();

    if (bannerPixmap.isNull()) {
        /*
            There is no widthForHeight() function, so we simulate it with a loop.
        */
        int candidateSubTitleWidth = qMin(512, 2 * qApp->desktop()->width() / 3);
        int delta = candidateSubTitleWidth >> 1;
        while (delta > 0) {
            if (subTitleLabel->heightForWidth(candidateSubTitleWidth - delta)
                        <= desiredSubTitleHeight)
                candidateSubTitleWidth -= delta;
            delta >>= 1;
        }

        subTitleLabel->setMinimumSize(candidateSubTitleWidth, desiredSubTitleHeight);

        QSize size = layout->totalMinimumSize();
        setMinimumSize(size);
        setMaximumSize(QWIDGETSIZE_MAX, size.height());
    } else {
        subTitleLabel->setMinimumSize(0, 0);
    }
    updateGeometry();
}

void QWizardHeader::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    //painter.drawPixmap(0, 0, bannerPixmap);

    int x = width() - 2;
    int y = height() - 2;
    const QPalette &pal = palette();
    painter.setPen(pal.mid().color());
    painter.drawLine(0, y, x, y);
    painter.setPen(pal.base().color());
    painter.drawPoint(x + 1, y);
    painter.drawLine(0, y + 1, x + 1, y + 1);
}

QSwitchWorkspaceDialog::QSwitchWorkspaceDialog(QSettings *settings,QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::QSwitchWorkspaceDialog)
{
    this->settings = settings;
    m_ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->setMargin(0);
    layout->setSpacing(3);
    layout->addSpacing(0);


    QWizardHeader* header = new QWizardHeader(this);
    header->setup(tr("Select a workspace"),tr("Chmcreator stores your projects in a folder called a workspace.\nChoose a workspace folder to use for this session."));
    layout->addWidget(header);

    QGridLayout *hLayout = new QGridLayout;

    hLayout->addWidget(new QLabel(tr("Workspace:")),0,0);

    comboBox = new QComboBox(this);
    comboBox->addItem("");
    comboBox->setEditable(true);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    hLayout->addWidget(comboBox,0,1);

    pushbutton = new QPushButton(tr("Browser..."));
    connect(pushbutton,SIGNAL(clicked()),this,SLOT(selectPath()));
    hLayout->addWidget(pushbutton,0,2);//,0,4);
    hLayout->setMargin(5);
    hLayout->setSpacing(3);

    hLayout->addWidget(new QLabel(""),1,1,Qt::AlignRight);

    QPushButton* okButton = new QPushButton("OK",this);
    okButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    hLayout->addWidget(okButton,2,1,Qt::AlignRight);
    QPushButton* cancelButton = new QPushButton("Cancel",this);
    hLayout->addWidget(cancelButton,2,2);

    layout->addLayout(hLayout);
    layout->addStretch(1);
    setLayout(layout);
    connect(this,SIGNAL(accepted()),this,SLOT(setvalue()));

    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    isaccepted = false;
}

void QSwitchWorkspaceDialog::setvalue()
{
    settings->setValue(WORKSPACE_PATH,comboBox->currentText());
    isaccepted = true;
}
void QSwitchWorkspaceDialog::selectPath()
{
    QString path = QFileDialog::getExistingDirectory(this);
    if(path!=QString::null){
        comboBox->removeItem(0);
        comboBox->addItem(path);
    }
}
QSwitchWorkspaceDialog::~QSwitchWorkspaceDialog()
{
    delete m_ui;
}

void QSwitchWorkspaceDialog::changeEvent(QEvent *e)
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
