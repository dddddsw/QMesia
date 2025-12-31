#include "GraphicsRotateTool.hpp"

namespace Mesia {
    GraphicsRotateTool::GraphicsRotateTool(QObject* parent) : GraphicsTool(RotateTool, parent) {
    }

    bool GraphicsRotateTool::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        return false;
    }

    bool GraphicsRotateTool::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        return false;
    }

    bool GraphicsRotateTool::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        return false;
    }

    bool GraphicsRotateTool::keyPressEvent(QKeyEvent* event) {
        return false;
    }
} // Mesia