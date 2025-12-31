#pragma once

#ifndef MKS_OBJECT_TREE_MODEL_HPP
#define MKS_OBJECT_TREE_MODEL_HPP
#include <functional>

namespace mks {
    class ObjectTreeItem;
    class ObjectTreeModel {
    public:
        ObjectTreeModel() {}
        ~ObjectTreeModel() {}

        [[nodiscard]] ObjectTreeItem *root() const { return m_root; }

        void addItem(ObjectTreeItem *parent, ObjectTreeItem *item) {}

        // callback
        using RowsInsertedCallback = std::function<void(ObjectTreeItem *parent, int first, int last)>;
        ObjectTreeModel& onRowsInserted(RowsInsertedCallback callback) {}

        using ColumnsInsertedCallback = std::function<void(ObjectTreeItem *parent, int first, int last)>;
        ObjectTreeModel& onColumnsInserted(ColumnsInsertedCallback callback) {}

        using RowsRemovedCallback = std::function<void(ObjectTreeItem *parent, int first, int last)>;
        ObjectTreeModel& onRowsRemoved(RowsRemovedCallback callback) {}

        using ColumnsRemovedCallback = std::function<void(ObjectTreeItem *parent, int first, int last)>;
        ObjectTreeModel& onColumnsRemoved(ColumnsRemovedCallback callback) {}

        using ColumnsRemovedCallback = std::function<void(ObjectTreeItem *parent, int first, int last)>;
        ObjectTreeModel& onDataChanged() {}

    private:
        ObjectTreeItem *m_root;
    };
} // namespace mks

#endif
