#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractItemModel>

class DataModel : QAbstractItemModel
{
public:
    explicit DataModel(QObject *parent = 0) : QAbstractItemModel(parent) {}
};

#endif // DATAMODEL_H
