#pragma once

#ifndef MESIA_GRAPHICS_RESIZE_TOOL_HPP
#define MESIA_GRAPHICS_RESIZE_TOOL_HPP

#include "GraphicsTool.hpp"

namespace Mesia {
    class GraphicsResizeTool : public GraphicsTool {
    public:
        explicit GraphicsResizeTool(QObject* parent);

        void reset() override;

    protected:
        bool mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        bool mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        bool mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
        bool keyPressEvent(QKeyEvent *event) override;

    private:
        qreal m_sx;
        qreal m_sy;
        QPointF m_origin;
    };
} // Mesia

#endif