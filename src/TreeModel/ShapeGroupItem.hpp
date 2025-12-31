#pragma once

#ifndef MELEOA_SHAPE_GROUP_ITEM_HPP
#define MELEOA_SHAPE_GROUP_ITEM_HPP

#include "ShapeBaseItem.hpp"

namespace Meleoa {
    class ShapeGroupItem;
    using ShapeGroupItemPtr = std::shared_ptr<ShapeGroupItem>;

    class ShapeGroupItem : public ObjectTreeItem {
    public:
        explicit ShapeGroupItem(const ObjectTreeItemPtr& parent = {}, std::vector<ShapeBaseItemPtr> members = {})
            : ObjectTreeItem(Group, parent), m_members(std::move(members)) {
        }

        ~ShapeGroupItem() override = default;

        [[nodiscard]] std::vector<ShapeBaseItemPtr> members() const { return m_members; }
        [[nodiscard]] std::size_t memberCount() const { return m_members.size(); }
        [[nodiscard]] Geometry::Transform transform() const { return m_transform; }
        void doPostTransform(const Geometry::Transform &trans) { m_transform *= trans; }

    private:
        Geometry::Transform m_transform;
        std::vector<ShapeBaseItemPtr> m_members;
    };
}

#endif
