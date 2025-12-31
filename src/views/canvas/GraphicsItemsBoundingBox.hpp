#pragma once

#ifndef MESIA_GRAPHICS_ITEMS_BOUNDING_BOX_HPP
#define MESIA_GRAPHICS_ITEMS_BOUNDING_BOX_HPP

#include <QGraphicsItem>
#include <QPen>

namespace Mesia {
    class GraphicsItemsBoundingBox {
    public:
        enum class HandlePosition {
            TopLeft,
            Top,
            TopRight,
            Left,
            Right,
            BottomLeft,
            Bottom,
            BottomRight,
            Center
        };

        enum class HandleType {
            Resize,
            Rotate,
            Shear,
            Move
        };

        enum class HandleStyle {
            Rectangle,
            Circle
        };

        struct Handle {
            HandleType type{};
            HandlePosition position{};
            QRectF rect;
        };

        GraphicsItemsBoundingBox();
        void translate(qreal dx, qreal dy);
        void setPen(const QPen &pen) { m_pen = pen; }
        void setBrush(const QBrush &brush) { m_brush = brush; }
        void setHandleSize(const qreal handleSize) { m_handleSize = handleSize; }
        void update(const QList<QGraphicsItem*> &items);
        void update(const QRectF &boundingRect);
        void draw(QPainter *painter) const;

        [[nodiscard]] const QList<Handle> &handles() const { return m_handles; }
        [[nodiscard]] const QRectF &rect() const { return m_boundingRect; }
        [[nodiscard]] std::optional<Handle> handleAt(const QPointF& scenePos) const;
        [[nodiscard]] bool isVisible() const { return !m_boundingRect.isNull(); }

    private:
        void update();

        QPen m_pen;
        QBrush m_brush;
        qreal m_handleSize;
        HandleStyle m_handleStyle;
        QRectF m_boundingRect;
        QList<Handle> m_handles;
    };

}

#endif
