#include <QGraphicsSceneMouseEvent>
#include "views/canvas/GraphicsScene.hpp"
#include "views/canvas/GraphicsView.hpp"
#include "views/canvas/GraphicsItem.hpp"
#include "GraphicsResizeTool.hpp"

namespace Mesia {
    GraphicsResizeTool::GraphicsResizeTool(QObject* parent) : GraphicsTool(ResizeTool, parent), m_sx(1), m_sy(1)
    {
    }

    void GraphicsResizeTool::reset()
    {
        m_sx = 1;
        m_sy = 1;
        m_origin = QPointF();
    }

    bool GraphicsResizeTool::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        return false;
    }

    bool GraphicsResizeTool::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        if (!(event->buttons() & Qt::LeftButton)) {
            return false;
        }
        if (!scene()->selectedItemsBoundingBox()->isVisible()) {
            return false;
        }

        const GraphicsItemsBoundingBox *boundingBox = scene()->selectedItemsBoundingBox();
        const auto handleOption = boundingBox->handleAt(event->scenePos());
        if (!handleOption.has_value() || handleOption.value().type != GraphicsItemsBoundingBox::HandleType::Resize) {
            return false;
        }

        const GraphicsItemsBoundingBox::Handle &handle = handleOption.value();
        const QPointF currentScenePos = event->scenePos();
        const QRectF oldBoundingRect = boundingBox->rect();
        QRectF newBoundingRect = oldBoundingRect;

        switch (handle.position) {
            case GraphicsItemsBoundingBox::HandlePosition::TopLeft:
                newBoundingRect.setTopLeft(currentScenePos);
                break;
            case GraphicsItemsBoundingBox::HandlePosition::Top:
                newBoundingRect.setTop(currentScenePos.y());
                break;
            case GraphicsItemsBoundingBox::HandlePosition::TopRight:
                newBoundingRect.setTopRight(currentScenePos);
                break;
            case GraphicsItemsBoundingBox::HandlePosition::Left:
                newBoundingRect.setLeft(currentScenePos.x());
                break;
            case GraphicsItemsBoundingBox::HandlePosition::Right:
                newBoundingRect.setRight(currentScenePos.x());
                break;
            case GraphicsItemsBoundingBox::HandlePosition::BottomLeft:
                newBoundingRect.setBottomLeft(currentScenePos);
                break;
            case GraphicsItemsBoundingBox::HandlePosition::Bottom:
                newBoundingRect.setBottom(currentScenePos.y());
                break;
            case GraphicsItemsBoundingBox::HandlePosition::BottomRight:
                newBoundingRect.setBottomRight(currentScenePos);
                break;
            default:
                break;
        }

        m_sx = newBoundingRect.width() / oldBoundingRect.width();
        m_sy = newBoundingRect.height() / oldBoundingRect.height();
        m_origin = handle.rect.center();

        if (m_sx != 1 && m_sy != 1) {
            for (const auto item : scene()->selectedItems()) {
                if (const auto graphicsItem = dynamic_cast<GraphicsItem*>(item)) {
                    graphicsItem->scale(m_sx, m_sy, item->mapFromScene(m_origin));
                }
            }
            scene()->selectedItemsBoundingBox()->update(newBoundingRect);
        }
        qDebug() << m_sx << m_sy << m_origin;
        return false;
    }

    bool GraphicsResizeTool::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        if (event->button() & Qt::LeftButton) {
            requestSwitchTool(SelectTool);
        }
        return false;
    }

    bool GraphicsResizeTool::keyPressEvent(QKeyEvent* event) {
        GraphicsTool::keyPressEvent(event);
        return false;
    }
} // Mesia