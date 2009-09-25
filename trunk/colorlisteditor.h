#ifndef COLORLISTEDITOR_H
#define COLORLISTEDITOR_H

#include <QComboBox>
#include "colorlisteditor.h"


QT_BEGIN_NAMESPACE
class QColor;
class QWidget;
QT_END_NAMESPACE

//! [0]
class ColorListEditor : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor USER true)

public:
    ColorListEditor(QWidget *widget = 0);

public:
    QColor color() const;
    void setColor(QColor c);

private:
    void populateList();
};
//! [0]

#endif
