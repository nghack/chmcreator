#ifndef QHTMLSOURCEEDITOR_H
#define QHTMLSOURCEEDITOR_H

 #include <QPlainTextEdit>
 #include <QObject>

 class QPaintEvent;
 class QResizeEvent;
 class QSize;
 class QWidget;

 class QLineNumberArea;


 class QHTMLSourceEditorCodeEditor : public QPlainTextEdit
 {
     Q_OBJECT

 public:
     QHTMLSourceEditorCodeEditor(QWidget *parent = 0);

     void lineNumberAreaPaintEvent(QPaintEvent *event);
     int lineNumberAreaWidth();

 protected:
     void resizeEvent(QResizeEvent *event);

 private slots:
     void updateLineNumberAreaWidth(int newBlockCount);
     void highlightCurrentLine();
     void updateLineNumberArea(const QRect &, int);

 private:
     QWidget *lineNumberArea;
 };


 class QLineNumberArea : public QWidget
 {
 public:
     QLineNumberArea(QHTMLSourceEditorCodeEditor *editor) : QWidget(editor) {
         codeEditor = editor;
     }

     QSize sizeHint() const {
         return QSize(codeEditor->lineNumberAreaWidth(), 0);
     }

 protected:
     void paintEvent(QPaintEvent *event) {
         codeEditor->lineNumberAreaPaintEvent(event);
     }

 private:
     QHTMLSourceEditorCodeEditor *codeEditor;
 };

#endif // QHTMLSOURCEEDITOR_H
