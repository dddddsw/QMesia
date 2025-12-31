#pragma once

#ifndef MKS_QCANVAS_MODEL_HPP
#define MKS_QCANVAS_MODEL_HPP

#include <QAbstractItemModel>
#include "Types.hpp"

namespace mks {
    class QCanvasModelPrivate;
    class QCanvasModel : public QAbstractItemModel {
    public:
        explicit QCanvasModel(QObject *parent = nullptr);
        ~QCanvasModel() override;

        void setHeaders(const QList<std::pair<LayerAttribute, QString>>& headers) const;

        //

        // override
        [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override; // NOLINT(google-default-arguments)
        [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override; // NOLINT(google-default-arguments)
        [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override; // NOLINT(google-default-arguments)
        [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;
        [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override; // NOLINT(google-default-arguments)
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override; // NOLINT(google-default-arguments)
        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override; // NOLINT(google-default-arguments)
        [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    private:
        friend class QCanvasModelPrivate;
        QScopedPointer<QCanvasModelPrivate> d_ptr;
    };
} // namespace mks

#endif
