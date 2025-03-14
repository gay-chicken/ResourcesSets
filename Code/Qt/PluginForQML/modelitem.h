#ifndef MODELITEM_H
#define MODELITEM_H

#include <QtQuick/QQuickPaintedItem>

class ModelItem : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(ModelItem)
public:
    explicit ModelItem(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
    ~ModelItem() override;
};

#endif // MODELITEM_H
