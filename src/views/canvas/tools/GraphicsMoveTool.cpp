#include "GraphicsMoveTool.hpp"
#include <QGraphicsSceneMouseEvent>
#include "views/canvas/GraphicsScene.hpp"
#include "views/canvas/GraphicsView.hpp"

namespace Mesia {
    bool GraphicsMoveTool::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        return false;
    }

    bool GraphicsMoveTool::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        if (!isMousePressed(event, Qt::LeftButton)) {
            return false;
        }

        const QPointF delta = event->scenePos() - event->lastScenePos();
        for (const auto items = scene()->selectedItems(); const auto item: items) {
            item->setPos(item->pos() + delta);
        }
        scene()->selectedItemsBoundingBox()->translate(delta.x(), delta.y());
        scene()->invalidate(QRectF(), QGraphicsScene::ForegroundLayer);
        return false;
    }

    bool GraphicsMoveTool::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        if (event->button() & Qt::LeftButton) {
            requestSwitchTool(SelectTool);
        }
        return false;
    }

    bool GraphicsMoveTool::keyPressEvent(QKeyEvent* event) {
        return GraphicsTool::keyPressEvent(event);
    }
    bool GraphicsMoveTool::drawForeground(QPainter* painter, const QRectF& rect)
    {
        scene()->selectedItemsBoundingBox()->draw(painter);

        return false;
    }
} // Mesia