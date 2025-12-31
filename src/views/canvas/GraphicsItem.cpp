/**
  ******************************************************************************
  * @file           : GraphicsItem.cpp
  * @brief          : None
  * @attention      : None
  * @date           : 2025/1/13
  ******************************************************************************
  */

#include <QDebug>
#include <QPainter>
#include "TreeModel/RectangleItem.hpp"
#include "GraphicsItem.hpp"

namespace {
    template<typename T>
    concept HasTypeValue = requires {
            { T::TypeValue } -> std::convertible_to<int>;
    };

    template <HasTypeValue T>
    T* convert_shape_to(const Meleoa::ShapeBaseItemPtr& shape) {
        return static_cast<int>(shape->shapeType()) == T::TypeValue ? static_cast<T*>(shape.get()) : nullptr;
    }

    QRectF computeRectangleBoundingRect(const Meleoa::ShapeBaseItemPtr& shape) {
        if (const auto rect = convert_shape_to<Meleoa::RectangleItem>(shape)) {
            return {rect->data().x(), rect->data().y(), rect->data().width(), rect->data().height()};
        }
        return {};
    }
    QRectF computeEllipseBoundingRect(const Meleoa::ShapeBaseItemPtr& shape) {
        if (const auto rect = convert_shape_to<Meleoa::RectangleItem>(shape)) {
            return {rect->data().x(), rect->data().y(), rect->data().width(), rect->data().height()};
        }
        return {};
    }
    QRectF computePolylineBoundingRect(const Meleoa::ShapeBaseItemPtr& shape) {
        if (const auto rect = convert_shape_to<Meleoa::RectangleItem>(shape)) {
            return {rect->data().x(), rect->data().y(), rect->data().width(), rect->data().height()};
        }
        return {};
    }
    QRectF computePathBoundingRect(const Meleoa::ShapeBaseItemPtr& shape) {
        if (const auto rect = convert_shape_to<Meleoa::RectangleItem>(shape)) {
            return {rect->data().x(), rect->data().y(), rect->data().width(), rect->data().height()};
        }
        return {};
    }
    QRectF computeTextBoundingRect(const Meleoa::ShapeBaseItemPtr& shape) {
        if (const auto rect = convert_shape_to<Meleoa::RectangleItem>(shape)) {
            return {rect->data().x(), rect->data().y(), rect->data().width(), rect->data().height()};
        }
        return {};
    }
    QRectF computeImageBoundingRect(const Meleoa::ShapeBaseItemPtr& shape) {
        if (const auto rect = convert_shape_to<Meleoa::RectangleItem>(shape)) {
            return {rect->data().x(), rect->data().y(), rect->data().width(), rect->data().height()};
        }
        return {};
    }
}

namespace Mesia {
    GraphicsItem::GraphicsItem(Meleoa::ShapeBaseItemPtr shape, QGraphicsItem* parent)
        : QGraphicsItem(parent),
          m_shape(std::move(shape)) {
        setFlag(ItemIsSelectable, true);
        setFlag(ItemSendsGeometryChanges, true);
        updateBoundingRect();
    }

    GraphicsItem::~GraphicsItem() {
        qDebug() << "~GraphicsItem";
    }

    Meleoa::ShapeBaseItem::ShapeType GraphicsItem::shapeType() const {
        return m_shape->shapeType();
    }

    QRectF GraphicsItem::boundingRect() const {
        // Rectangle rect = ShapeHelper::boundingRect(m_shape.get());
        // Point center = rect.center();
        //
        // QRectF br(0, 0, rect.width(), rect.height());
        // br.moveCenter(QPointF(center.x(), center.y()));

        return m_boundingRect;
    }

    void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        painter->save();

        painter->setBrush(brush());
        painter->setPen(pen());
        painter->setRenderHint(QPainter::Antialiasing);

        switch (shapeType()) {
            case Meleoa::ShapeBaseItem::Polyline:
                drawPolyline(painter);
                break;
            case Meleoa::ShapeBaseItem::Rectangle:
                drawRectangle(painter);
                break;
            case Meleoa::ShapeBaseItem::Ellipse:
                drawEllipse(painter);
                break;
            case Meleoa::ShapeBaseItem::Path:
                drawPath(painter);
                break;
            case Meleoa::ShapeBaseItem::Text:
            case Meleoa::ShapeBaseItem::Image:
                break;
        }

        painter->restore();
    }

    QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant& value) {
        if (change == ItemTransformHasChanged) {
            int a = value.toInt();
        }
        return QGraphicsItem::itemChange(change, value);
    }

    QBrush GraphicsItem::brush() const {
        return m_brush;
    }

    QPen GraphicsItem::pen() const {
        return m_pen;
    }

    void GraphicsItem::setBrush(const QBrush &brush) {
        m_brush = brush;
    }

    void GraphicsItem::setPen(const QPen &pen) {
        m_pen = pen;
    }

    void GraphicsItem::scale(const qreal sx, const qreal sy, const QPointF& origin)
    {
        const QTransform oldTrans = transform();
        const QPointF center = oldTrans.map(origin);

        QTransform newTrans;
        newTrans.translate(center.x(), center.y());
        newTrans.scale(sx, sy);
        newTrans.translate(-center.x(), -center.y());

        setTransform(oldTrans * newTrans);
    }

    void GraphicsItem::rotate(const qreal angle, const QPointF& origin)
    {
        // m_rotation = std::fmod(m_rotation + rotation, 360);
        // setData(DataKey::Rotation, m_rotation);
        //
        // QTransform oldTrans = transform();
        // QPointF center = oldTrans.map(origin);
        //
        // QTransform newTrans;
        // newTrans.translate(center.x(), center.y());
        // newTrans.rotate(rotation);
        // newTrans.translate(-center.x(), -center.y());
        //
        // setTransform(oldTrans * newTrans);
    }

    void GraphicsItem::mirrored(bool horizontal, bool vertical, const QPointF& origin)
    {

    }

    void GraphicsItem::drawRectangle(QPainter *painter) const {
        if (const auto rectangle = convert_shape_to<Meleoa::RectangleItem>(m_shape)) {
            const QRectF rect{rectangle->data().x(), rectangle->data().y(),
                rectangle->data().width(), rectangle->data().height()
            };
            painter->drawRect(rect);
        }
        // auto rectangle = dynamic_cast<Rectangle*>(m_shape.get());
        // if (!rectangle) {
        //     return;
        // }
        // Point center = rectangle->center();
        //
        // QRectF rect(0, 0, rectangle->width(), rectangle->height());
        // rect.moveCenter(QPointF(center.x(), center.y()));
        //
        // m_data = QVariant::fromValue(rect);
        // painter->drawRect(rect);
    }

    void GraphicsItem::drawEllipse(QPainter *painter) {
        // auto ellipse = dynamic_cast<Ellipse*>(m_shape.get());
        // if (!ellipse) {
        //     return;
        // }
        // Point center = ellipse->center();
        //
        // QRectF rect(0, 0, ellipse->width(), ellipse->height());
        // rect.moveCenter(QPointF(center.x(), center.y()));
        // painter->drawEllipse(rect);
    }

    void GraphicsItem::drawPolyline(QPainter *painter) {
        // auto polyline = dynamic_cast<Polyline*>(m_shape.get());
        // if (!polyline) {
        //     return;
        // }
        // std::vector<Point> points = polyline->points();
        // if (points.size() < 2) {
        //     return;
        // }
        // for (int i = 1; i < points.size(); ++i) {
        //     const Point &prev = points[i - 1];
        //     const Point &curr = points[i];
        //     painter->drawLine(QPointF(prev.x(), prev.y()), QPointF(curr.x(), curr.y()));
        // }
    }

    void GraphicsItem::drawPolygon(QPainter *painter) {
        // auto polygon = dynamic_cast<Polyline*>(m_shape.get());
        // if (!polygon) {
        //     return;
        // }
        // std::vector<Point> points = polygon->points();
        // if (points.size() < 2) {
        //     return;
        // }
        //
        // int pointCount = static_cast<int>(points.size());
        // for (int i = 0; i < pointCount; ++i) {
        //     const Point &curr = points[i];
        //     const Point &next = points[(i + 1) % pointCount];
        //     painter->drawLine(QPointF(curr.x(), curr.y()), QPointF(next.x(), next.y()));
        // }
    }

    void GraphicsItem::drawPath(QPainter *painter) {
        // auto path = dynamic_cast<Path*>(m_shape.get());
        // if (!path) {
        //     return;
        // }
        //
        // for (const auto &polyline : path->toPolylineList()) {
        //     std::vector<Point> points = polyline.points();
        //     if (points.size() < 2) {
        //         return;
        //     }
        //
        //     QPainterPath qPath;
        //     qPath.moveTo(points[0].x(), points[0].y());
        //     int pointCount = static_cast<int>(points.size());
        //     for (int i = 1; i < pointCount; ++i) {
        //         qPath.lineTo(points[i].x(), points[i].y());
        //     }
        //
        //     painter->drawPath(qPath);
        // }
    }

    void GraphicsItem::updateBoundingRect() {
        switch (shapeType()) {
        case Meleoa::ShapeBaseItem::Polyline:
            break;
        case Meleoa::ShapeBaseItem::Rectangle:
            if (const auto rectangle = convert_shape_to<Meleoa::RectangleItem>(m_shape)) {
                m_boundingRect = QRectF(rectangle->data().x(), rectangle->data().y(),
                    rectangle->data().width(), rectangle->data().height()
                );
            }
            break;
        case Meleoa::ShapeBaseItem::Ellipse:
        case Meleoa::ShapeBaseItem::Path:
        case Meleoa::ShapeBaseItem::Text:
        case Meleoa::ShapeBaseItem::Image:
            break;
        }
    }

    void GraphicsItem::updateTransform() const {
        const QTransform trans = transform();
        m_shape->transform().reset(trans.m11(), trans.m12(), trans.m13(),
                                   trans.m21(), trans.m22(), trans.m23(),
                                   trans.m31(), trans.m32(), trans.m33());
    }
}
