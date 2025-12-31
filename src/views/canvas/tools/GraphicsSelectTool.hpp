#pragma once

#ifndef MESIA_GRAPHICS_ITEM_SELECT_TOOL_HPP
#define MESIA_GRAPHICS_ITEM_SELECT_TOOL_HPP

#include <QPen>
#include "GraphicsTool.hpp"

namespace Mesia {
    class GraphicsSelectTool : public GraphicsTool {
    public:
        explicit GraphicsSelectTool(QObject* parent);

    protected:
        bool mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        bool mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        bool mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
        bool keyPressEvent(QKeyEvent* event) override;
        bool drawForeground(QPainter* painter, const QRectF& rect) override;

    private:
        void updateCursorShape(const QGraphicsSceneMouseEvent* event) const;
        void updateCursorShape(Qt::CursorShape cursorShape) const;
    };
}

#endif
