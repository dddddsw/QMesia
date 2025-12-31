#pragma once

#ifndef MKS_OBJECT_TREE_ITEM_HPP
#define MKS_OBJECT_TREE_ITEM_HPP

#include <memory>
#include <utility>
#include <vector>

namespace Meleoa {
    class ObjectTreeItem;
    using ObjectTreeItemPtr = std::shared_ptr<ObjectTreeItem>;
    
    class ObjectTreeItem {
    public:
        enum Type { Layer, Shape, Group };

        explicit ObjectTreeItem(const Type type, ObjectTreeItemPtr parent = {}) : m_isValid(true),
            m_type(type), m_parent(std::move(parent)) {
        }

        virtual ~ObjectTreeItem() = default;

        [[nodiscard]] ObjectTreeItemPtr parent() const { return m_parent; }
        void setParent(const ObjectTreeItemPtr& parent) { m_parent = parent; }
        void setValid(const bool valid) { m_isValid = valid; }

        [[nodiscard]] const std::vector<ObjectTreeItemPtr>& children() const { return m_children; }
        [[nodiscard]] ObjectTreeItemPtr child(int index) const { return m_children[index]; }
        [[nodiscard]] std::size_t childCount() const { return m_children.size(); }
        [[nodiscard]] bool isValid() const { return m_isValid; }
        [[nodiscard]] Type type() const { return m_type; }

        // void appendChild(ObjectTreeItemPtr child);
        // void insertChild(int index, ObjectTreeItemPtr child);
        // void removeChild(ObjectTreeItemPtr child);
        // ObjectTreeItemPtr takeChild(int index);


    protected:
        bool m_isValid;
        Type m_type;
        ObjectTreeItemPtr m_parent;
        std::vector<ObjectTreeItemPtr> m_children;
    };
} // namespace mks

#endif
