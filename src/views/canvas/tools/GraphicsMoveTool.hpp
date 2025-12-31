#pragma once

#ifndef MESIA_GRAPHICS_MOVE_TOOL_HPP
#define MESIA_GRAPHICS_MOVE_TOOL_HPP

#include "GraphicsTool.hpp"

namespace Mesia {
    class GraphicsMoveTool : public GraphicsTool {
    public:
        explicit GraphicsMoveTool(QObject* parent) : GraphicsTool(MoveTool, parent) {
        }

    protected:
        bool mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        bool mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        bool mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
        bool keyPressEvent(QKeyEvent *event) override;
        bool drawForeground(QPainter* painter, const QRectF& rect) override;
    };
}

#endif
