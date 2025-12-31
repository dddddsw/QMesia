#include <QGraphicsSceneMouseEvent>
#include "GraphicsTool.hpp"

#include "views/canvas/GraphicsScene.hpp"

namespace Mesia {
    GraphicsTool::GraphicsTool(const Type type, QObject* parent) :
        QObject(parent),
        m_scene(nullptr),
        m_view(nullptr),
        m_type(type) {}

    bool GraphicsTool::isMousePressed(const QGraphicsSceneMouseEvent* event, const Qt::MouseButton button) {
        return event->buttons() & button;
    }

    QRectF GraphicsTool::boundingRect(const QList<QGraphicsItem*>& items) {
        if (items.isEmpty()) {
            return {};
        }

        QRectF totalRect = items.first()->mapRectToScene(items.first()->boundingRect());
        for (int i = 1; i < items.size(); ++i) {
            const auto item = items[i];
            QRectF rect = item->mapRectToScene(item->boundingRect());
            totalRect = totalRect.united(rect);
        }
        return totalRect;
    }

    bool GraphicsTool::hasSelectedItems() const {
        return scene()->selectedItems().isEmpty();
    }

    QList<QGraphicsItem*> GraphicsTool::itemsAt(const QPointF& scenePos) const {
        return scene()->items(scenePos);
    }
} // Mesia