#include "GraphicsItemsBoundingBox.hpp"
#include <QPainter>

namespace Mesia {
    GraphicsItemsBoundingBox::GraphicsItemsBoundingBox() :
        m_pen(Qt::red, 2),
        m_handleSize(10),
        m_handleStyle(HandleStyle::Circle)
    {
        m_pen.setCosmetic(true);
        m_handles.emplace_back(HandleType::Resize, HandlePosition::TopLeft, QRectF(0, 0, m_handleSize, m_handleSize));
        m_handles.emplace_back(HandleType::Resize, HandlePosition::Top, QRectF(0, 0, m_handleSize, m_handleSize));
        m_handles.emplace_back(HandleType::Resize, HandlePosition::Left, QRectF(0, 0, m_handleSize, m_handleSize));
        m_handles.emplace_back(HandleType::Resize, HandlePosition::TopRight, QRectF(0, 0, m_handleSize, m_handleSize));
        m_handles.emplace_back(HandleType::Move, HandlePosition::Center, QRectF(0, 0, m_handleSize, m_handleSize));
        m_handles.emplace_back(HandleType::Resize, HandlePosition::BottomLeft, QRectF(0, 0, m_handleSize, m_handleSize));
        m_handles.emplace_back(HandleType::Resize, HandlePosition::Right, QRectF(0, 0, m_handleSize, m_handleSize));
        m_handles.emplace_back(HandleType::Resize, HandlePosition::Bottom, QRectF(0, 0, m_handleSize, m_handleSize));
        m_handles.emplace_back(HandleType::Resize, HandlePosition::BottomRight, QRectF(0, 0, m_handleSize, m_handleSize));
    }

    void GraphicsItemsBoundingBox::translate(const qreal dx, const qreal dy)
    {
        m_boundingRect.translate(dx, dy);
        update();
    }

    void GraphicsItemsBoundingBox::update(const QList<QGraphicsItem*>& items)
    {
        if (items.isEmpty()) {
            m_boundingRect = QRectF();
            return;
        }

        m_boundingRect = items.first()->mapRectToScene(items.first()->boundingRect());
        for (int i = 1; i < items.size(); ++i) {
            const auto item = items[i];
            QRectF rect = item->mapRectToScene(item->boundingRect());
            m_boundingRect = m_boundingRect.united(rect);
        }

        update();
    }
    void GraphicsItemsBoundingBox::update(const QRectF& boundingRect)
    {
        m_boundingRect = boundingRect;
        update();
    }

    void GraphicsItemsBoundingBox::draw(QPainter* painter) const
    {
        if (m_boundingRect.isNull()) {
            return;
        }

        painter->save();

        const QTransform originalTransform = painter->transform();
        painter->setTransform(QTransform());

        painter->setPen(m_pen);
        painter->setBrush(m_brush);

        const qreal half = m_handleSize / 2.0;

        for (auto& [type, position, rect]  : m_handles) {
            QPointF deviceCenter = originalTransform.map(rect.center());
            QRectF deviceRect(deviceCenter.x() - half, deviceCenter.y() - half,
                              m_handleSize, m_handleSize);

            if (m_handleStyle == HandleStyle::Rectangle) {
                painter->drawRect(deviceRect);
            } else {
                painter->drawEllipse(deviceRect);
            }
        }

        painter->restore();
    }

    std::optional<GraphicsItemsBoundingBox::Handle> GraphicsItemsBoundingBox::handleAt(const QPointF& scenePos) const
    {
        for (const Handle &handle : m_handles) {
            if (handle.rect.contains(scenePos)) {
                return handle;
            }
        }
        return {};
    }

    void GraphicsItemsBoundingBox::update()
    {
        const qreal middleX = m_boundingRect.x() + m_boundingRect.width() / 2;
        const qreal middleY = m_boundingRect.y() + m_boundingRect.height() / 2;

        for (auto& [type, position, rect] : m_handles) {
            switch (position) {
                case HandlePosition::TopLeft: {
                    rect.moveCenter(m_boundingRect.topLeft());
                    break;
                }
                case HandlePosition::Top: {
                    rect.moveCenter(QPointF(middleX, m_boundingRect.top()));
                    break;
                }
                case HandlePosition::TopRight: {
                    rect.moveCenter(m_boundingRect.topRight());
                    break;
                }
                case HandlePosition::Right: {
                    rect.moveCenter(QPointF(m_boundingRect.right(), middleY));
                    break;
                }
                case HandlePosition::BottomRight: {
                    rect.moveCenter(m_boundingRect.bottomRight());
                    break;
                }
                case HandlePosition::Bottom: {
                    rect.moveCenter(QPointF(middleX, m_boundingRect.bottom()));
                    break;
                }
                case HandlePosition::BottomLeft: {
                    rect.moveCenter(m_boundingRect.bottomLeft());
                    break;
                }
                case HandlePosition::Left: {
                    rect.moveCenter(QPointF(m_boundingRect.x(), middleY));
                    break;
                }
                case HandlePosition::Center: {
                    rect.moveCenter(m_boundingRect.center());
                    break;
                }
            }
        }
    }
} // namespace Mesia
