#pragma once

#ifndef MELEOA_RECTANGLE_ITEM_HPP
#define MELEOA_RECTANGLE_ITEM_HPP

#include <Meleoa/Geometry/Rectangle.hpp>

#include "ShapeBaseItem.hpp"
#include "ShapeBaseItem.hpp"
#include "ShapeBaseItem.hpp"

namespace Meleoa {
    class RectangleItem final : public ShapeBaseItem {
    public:
        static constexpr int TypeValue = Rectangle;

        explicit RectangleItem(const Geometry::Rectangle& rectangle, const ObjectTreeItemPtr& parent = {})
            : ShapeBaseItem(Rectangle, parent), m_rectangle(rectangle) {
        }

        Geometry::Rectangle& data() { return m_rectangle; }

    private:
        Geometry::Rectangle m_rectangle;
    };
}

#endif
