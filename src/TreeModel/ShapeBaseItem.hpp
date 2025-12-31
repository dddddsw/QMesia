#pragma once

#ifndef MELEOA_SHAPE_TREE_ITEM_HPP
#define MELEOA_SHAPE_TREE_ITEM_HPP

#include <Meleoa/Geometry/Transform.hpp>
#include "ObjectTreeItem.hpp"

namespace Meleoa {
    class ShapeBaseItem;
    using ShapeBaseItemPtr = std::shared_ptr<ShapeBaseItem>;

    class ShapeBaseItem : public ObjectTreeItem {
    public:
        enum ShapeType { Rectangle, Ellipse, Polyline, Path, Text, Image };

        explicit ShapeBaseItem(const ShapeType shapeType, const ObjectTreeItemPtr& parent = {}) :
            ObjectTreeItem(Shape, parent), m_shapeType(shapeType) {
        }

        ~ShapeBaseItem() override = default;

        [[nodiscard]] ShapeType shapeType() const { return m_shapeType; }
        [[nodiscard]] Geometry::Transform& transform() { return m_transform; }

        void doPostTransform(const Geometry::Transform &trans) { m_transform *= trans; }

    private:
        Geometry::Transform m_transform;
        ShapeType m_shapeType;
    };
}

#endif
