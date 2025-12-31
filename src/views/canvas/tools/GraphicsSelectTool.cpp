#include "GraphicsSelectTool.hpp"
#include <QGraphicsSceneMouseEvent>
#include "views/canvas/GraphicsScene.hpp"
#include "views/canvas/GraphicsView.hpp"

namespace Mesia {
    GraphicsSelectTool::GraphicsSelectTool(QObject* parent) : GraphicsTool(SelectTool, parent) {}

    bool GraphicsSelectTool::mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        if (!scene()->selectedItemsBoundingBox()->isVisible()) {
            return true;
        }

        const auto handleOption = scene()->selectedItemsBoundingBox()->handleAt(event->scenePos());
        if (!handleOption.has_value()) {
            return false;
        }

        switch (handleOption.value().type) {
            case GraphicsItemsBoundingBox::HandleType::Resize:
                requestSwitchTool(ResizeTool);
                break;
            case GraphicsItemsBoundingBox::HandleType::Move:
                requestSwitchTool(MoveTool);
                break;
            case GraphicsItemsBoundingBox::HandleType::Rotate:
            case GraphicsItemsBoundingBox::HandleType::Shear:
                break;
        }
        return false;
    }

    bool GraphicsSelectTool::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
    {
        updateCursorShape(event);
        return false;
    }

    bool GraphicsSelectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
    {
        GraphicsTool::mouseReleaseEvent(event);
        return false;
    }

    bool GraphicsSelectTool::keyPressEvent(QKeyEvent* event) {
        return false;
    }

    bool GraphicsSelectTool::drawForeground(QPainter* painter, const QRectF& rect)
    {
        scene()->selectedItemsBoundingBox()->draw(painter);
        return false;
    }

    void GraphicsSelectTool::updateCursorShape(const QGraphicsSceneMouseEvent* event) const
    {
        const GraphicsItemsBoundingBox* selectedItemsBoundingBox = scene()->selectedItemsBoundingBox();
        if (selectedItemsBoundingBox->rect().isNull()) {
            return;
        }

        Qt::CursorShape cursorShape = Qt::ArrowCursor;
        for (auto& [type, position, rect] : selectedItemsBoundingBox->handles()) {
            if (!rect.contains(event->scenePos())) {
                continue;
            }
            switch (position) {
                case GraphicsItemsBoundingBox::HandlePosition::TopLeft:
                case GraphicsItemsBoundingBox::HandlePosition::BottomRight: {
                    cursorShape = Qt::SizeFDiagCursor;
                    break;
                }
                case GraphicsItemsBoundingBox::HandlePosition::Top:
                case GraphicsItemsBoundingBox::HandlePosition::Bottom: {
                    cursorShape = Qt::SizeVerCursor;
                    break;
                }
                case GraphicsItemsBoundingBox::HandlePosition::TopRight:
                case GraphicsItemsBoundingBox::HandlePosition::BottomLeft: {
                    cursorShape = Qt::SizeBDiagCursor;
                    break;
                }
                case GraphicsItemsBoundingBox::HandlePosition::Left:
                case GraphicsItemsBoundingBox::HandlePosition::Right: {
                    cursorShape = Qt::SizeHorCursor;
                    break;
                }
                case GraphicsItemsBoundingBox::HandlePosition::Center: {
                    cursorShape = Qt::SizeAllCursor;
                    break;
                }
            }
            break;
        }
        updateCursorShape(cursorShape);
    }

    void GraphicsSelectTool::updateCursorShape(const Qt::CursorShape cursorShape) const
    {
        if (view()->cursor().shape() != cursorShape) {
            view()->setCursor(QCursor(cursorShape));
        }
    }
}
