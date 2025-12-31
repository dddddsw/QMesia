#include "QCanvasModel.hpp"
#include "ObjectTreeItem.hpp"
#include "QCanvasModelPrivate.hpp"

namespace mks {
    QCanvasModel::QCanvasModel(QObject* parent) : QAbstractItemModel(parent), d_ptr(new QCanvasModelPrivate) {} // NOLINT

    QCanvasModel::~QCanvasModel() = default;

    void QCanvasModel::setHeaders(const QList<std::pair<LayerAttribute, QString>>& headers) const {
        d_ptr->m_headers.clear();
        for (const auto &[attr, name] : headers) {
            d_ptr->m_headers.emplace_back(attr, name.toStdString());
        }
    }

    int QCanvasModel::rowCount(const QModelIndex& parent) const { // NOLINT
        ObjectTreeItem* parentItem;

        if (!parent.isValid()) {
            parentItem = d_ptr->m_treeModel.root();
        } else {
            parentItem = static_cast<ObjectTreeItem*>(parent.internalPointer());
        }

        return static_cast<int>(parentItem->childCount());
    }

    int QCanvasModel::columnCount(const QModelIndex& parent) const { // NOLINT
        Q_UNUSED(parent)
        return 1;
    }

    QModelIndex QCanvasModel::index(int row, int column, const QModelIndex& parent) const { // NOLINT
        if (!hasIndex(row, column, parent)) {
            return {};
        }

        ObjectTreeItem* parentItem;
        if (!parent.isValid()) {
            parentItem = d_ptr->m_treeModel.root();
        } else {
            parentItem = static_cast<ObjectTreeItem*>(parent.internalPointer());
        }

        if (const ObjectTreeItem* childItem = parentItem->child(row)) {
            return createIndex(row, column, childItem);
        }

        return {};
    }

    QModelIndex QCanvasModel::parent(const QModelIndex& index) const {
        if (!index.isValid()) {
            return {};
        }

        const auto* childItem = static_cast<ObjectTreeItem*>(index.internalPointer());
        const ObjectTreeItem* parentItem = childItem->parent();

        if (parentItem == d_ptr->m_treeModel.root() || parentItem == nullptr) {
            return {};
        }

        for (int i = 0; i < parentItem->children().size(); ++i) {
            auto child = parentItem->children().at(i);
            if (child == childItem) {
                return createIndex(i, 0, parentItem);
            }
        }

        return {};
    }

    QVariant QCanvasModel::data(const QModelIndex& index, int role) const { // NOLINT
        if (!index.isValid()) {
            return {};
        }

        auto* item = static_cast<ObjectTreeItem*>(index.internalPointer());
        if (!item) {
            return {};
        }

        if (role != Qt::DisplayRole) {
            return {};
        }

        if (item->type() == ObjectTreeItem::Layer) {
            const int attrIndex = index.column();
            auto layerItem = static_cast<LayerTreeItem*>(item); // NOLINT
            switch (static_cast<LayerAttribute>(attrIndex)) {
            case LayerAttribute::Name: {
                return QVariant::fromValue(layerItem->name());
            }
            case LayerAttribute::Mode: {
                return QVariant::fromValue(layerItem->mode());
            }
            case LayerAttribute::Speed: {
                return QVariant::fromValue(layerItem->speed());
            }
            case LayerAttribute::Power: {
                return QVariant::fromValue(layerItem->power());
            }
            case LayerAttribute::Output: {
                return QVariant::fromValue(layerItem->output());
            }
            case LayerAttribute::AssistGas: {
                return QVariant::fromValue(layerItem->assistGas());
            }
            case LayerAttribute::Visibility: {
                return QVariant::fromValue(layerItem->visible());
            }
            default: {
                break;
            }
            }
        }
        return {};
    }

    bool QCanvasModel::setData(const QModelIndex& index, const QVariant& value, int role) { // NOLINT
        if (!index.isValid()) {
            return false;
        }

        auto* item = static_cast<ObjectTreeItem*>(index.internalPointer());
        if (!item) {
            return false;
        }

        if (role != Qt::DisplayRole) {
            return false;
        }

        if (item->type() == ObjectTreeItem::Layer) {
            const int attrIndex = index.column();
            auto layerItem = static_cast<LayerTreeItem*>(item); // NOLINT
            switch (static_cast<LayerAttribute>(attrIndex)) {
            case LayerAttribute::Name: {
                layerItem->setName(value.toString().toStdString());
                return true;
            }
            case LayerAttribute::Mode: {
                layerItem->setMode(value.value<LayerMode>());
                return true;
            }
            case LayerAttribute::Speed: {
                layerItem->setSpeed(value.toFloat());
                return true;
            }
            case LayerAttribute::Power: {
                layerItem->setPower(value.toFloat());
                return true;
            }
            case LayerAttribute::Output: {
                layerItem->setOutput(value.toBool());
                return true;
            }
            case LayerAttribute::AssistGas: {
                layerItem->setAssistGas(value.toBool());
                return true;
            }
            case LayerAttribute::Visibility: {
                layerItem->setVisible(value.toBool());
                return true;
            }
            default: break;
            }
        }
        return false;
    }

    QVariant QCanvasModel::headerData(int section, Qt::Orientation orientation, int role) const {
        return QAbstractItemModel::headerData(section, orientation, role);
    }

    Qt::ItemFlags QCanvasModel::flags(const QModelIndex& index) const { return QAbstractItemModel::flags(index); }
} // namespace mks
