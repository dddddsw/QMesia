#pragma once

#ifndef MESIA_GRAPHICS_ROTATE_TOOL_HPP
#define MESIA_GRAPHICS_ROTATE_TOOL_HPP

#include "GraphicsTool.hpp"

namespace Mesia {
    class GraphicsRotateTool : public GraphicsTool {
    public:
        explicit GraphicsRotateTool(QObject* parent);

    protected:
        bool mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        bool mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        bool mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
        bool keyPressEvent(QKeyEvent *event) override;
    };
}

#endif