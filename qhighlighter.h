#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QHash>
#include <QSyntaxHighlighter>
#include "qhighlighter.h"
// based on http://doc.trolltech.com/qq/qq21-syntaxhighlighter.html

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:

    Highlighter(QTextDocument *document);

    enum Construct {
        DocType,
        Entity,
        Tag,
        Comment,
        AttributeName,
        AttributeValue
    };

protected:
    enum State {
        State_Text = -1,
        State_DocType,
        State_Comment,
        State_TagStart,
        State_TagName,
        State_InsideTag,
        State_AttributeName,
        State_SingleQuote,
        State_DoubleQuote,
        State_AttributeValue,
    };

    void highlightBlock(const QString &text);

private:
    QHash<int, QColor> m_colors;
};


#endif // HIGHLIGHTER_H
