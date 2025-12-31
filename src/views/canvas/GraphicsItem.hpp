#ifndef MESIA_GRAPHICS_ITEM_H
#define MESIA_GRAPHICS_ITEM_H

#include <memory>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include "TreeModel/ShapeBaseItem.hpp"

namespace Mesia {
    class GraphicsItem : public QGraphicsItem {
    public:
        explicit GraphicsItem(Meleoa::ShapeBaseItemPtr shape, QGraphicsItem *parent = nullptr);
        ~GraphicsItem() override;

        [[nodiscard]] Meleoa::ShapeBaseItem::ShapeType shapeType() const;
        [[nodiscard]] QRectF boundingRect() const override;
        [[nodiscard]] QBrush brush() const;
        [[nodiscard]] QPen pen() const;

        void setBrush(const QBrush &brush);
        void setPen(const QPen &pen);

        void scale(qreal sx, qreal sy, const QPointF &origin);
        void rotate(qreal angle, const QPointF &origin);
        void mirrored(bool horizontal, bool vertical, const QPointF &origin);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    private:
        void updateBoundingRect();
        void updateTransform() const;

        void drawRectangle(QPainter *painter) const;
        void drawEllipse(QPainter *painter);
        void drawPolyline(QPainter *painter);
        void drawPolygon(QPainter *painter);
        void drawPath(QPainter *painter);

        QBrush m_brush;
        QPen m_pen;
        Meleoa::ShapeBaseItemPtr m_shape;
        QVariant m_data;
        QRectF m_boundingRect;
    };
}

#endif //_GraphicsItem_H
