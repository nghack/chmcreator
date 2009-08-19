#include <QtGui>

#include "colorlisteditor.h"

ColorListEditor::ColorListEditor(QWidget *widget) : QComboBox(widget)
{
    populateList();
}

//! [0]
QColor ColorListEditor::color() const
{
    return qVariantValue<QColor>(itemData(currentIndex(), Qt::DecorationRole));
}
//! [0]

//! [1]
void ColorListEditor::setColor(QColor color)
{
    setCurrentIndex(findData(color, int(Qt::DecorationRole)));
}
//! [1]

//! [2]
void ColorListEditor::populateList()
{
    QStringList colorNames = QColor::colorNames();

    for (int i = 0; i < colorNames.size(); ++i) {
        QColor color(colorNames[i]);

        insertItem(i, colorNames[i]);
        setItemData(i, color, Qt::DecorationRole);
    }
}
//! [2]
