#ifndef QTREEMODELHANDLER_H
#define QTREEMODELHANDLER_H

#include "qhhchandler.h"
#include "QTreeModel.h"

class QTreeModelHandler : public QHHCHandler
{
public:
    QTreeModelHandler(QTreeModel* model);
    virtual ~QTreeModelHandler();
    virtual void startElement(const QString& tagName,const QMap<QString,QString>& attr);
    virtual void endElement(const QString& tagName);
    virtual void* getTopics();
private:
    QTreeModel* result;
    int depth;
    QString line;
};

#endif // QTREEMODELHANDLER_H
