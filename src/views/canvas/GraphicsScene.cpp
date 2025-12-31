#include "GraphicsScene.hpp"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <iostream>
#include "GraphicsItem.hpp"
#include "GraphicsView.hpp"
#include "InteractionModeManager.hpp"
#include "TreeModel/RectangleItem.hpp"
#include "tools/GraphicsToolManager.hpp"
#include "util/VectorPathUtil.hpp"

namespace Mesia {
    GraphicsScene::GraphicsScene(QObject* parent) :
        QGraphicsScene(parent),
        m_interactionModeManager(new InteractionModeManager(this)),
        m_graphicsToolManager(nullptr),
        m_view(nullptr)
    {
        setSceneRect(0, 0, 500, 500);
        //        setSceneRect(-5000, -5000, 10000, 10000);
        //        setAction(QSharedPointer<CreateRectangleAction>::create());

        QPainterPath textPath;
        QFont font;
        font.setPointSizeF(80);
        // textPath.addText(250, 250, font, "Test");
        textPath.addEllipse(0, 0, 100, 100);

        Meleoa::Geometry::VectorPath customPath;
        for (int i = 0; i < textPath.elementCount(); i++) {
            auto e = textPath.elementAt(i);
            switch (e.type) {
                case QPainterPath::MoveToElement:
                    customPath.moveTo(e.x, e.y);
                    break;
                case QPainterPath::LineToElement:
                    customPath.lineTo(e.x, e.y);
                    break;
                case QPainterPath::CurveToElement:
                    customPath.cubicTo(e.x, e.y, textPath.elementAt(i + 1).x, textPath.elementAt(i + 1).y,
                                       textPath.elementAt(i + 2).x, textPath.elementAt(i + 2).y);
                    break;
                case QPainterPath::CurveToDataElement:
                    break;
            }
        }

        QTransform transform;
        transform.rotate(54).translate(-87, 23).scale(-4.8, 3.6).rotate(-41);
        auto p = transform.map(textPath);

        std::vector<QPointF> points;
        for (int i = 0; i < p.elementCount(); i++) {
            auto e = p.elementAt(i);
            points.emplace_back(e.x, e.y);
            std::cerr << std::format("{}, {}", e.x, e.y) << std::endl;
        }

        addPath(fromMeleoaVectorPath(customPath));

        Meleoa::Geometry::Rectangle rect{0, 0, 100, 100};
        auto rectangle = std::make_shared<Meleoa::RectangleItem>(rect);
        auto item = new GraphicsItem(rectangle);

        addItem(item);

        // QTimer::singleShot(3000, [item, this] {
        //     item->setTransform(QTransform::fromScale(2, 1));
        //     m_graphicsToolManager->setSelectedItems(selectedItems());
        //     invalidate(QRectF(), ForegroundLayer);
        // });

        //
        //        std::vector<QPolygonF> polygons;
        //        auto polylineList = customPath.toPolylineList();
        //        for (const auto &polyline : polylineList) {
        //            QPolygonF polygon;
        //            for (const auto &point : polyline.points()) {
        //                polygon.append({point.x(), point.y()});
        //            }
        //            polygons.push_back(polygon);
        //        }
        //
        //        for (const auto &polygon : polygons) {
        //            addPolygon(polygon);
        //        }

        connect(this, &GraphicsScene::selectionChanged, this, &GraphicsScene::onSelectionChanged);
    }

    GraphicsScene::~GraphicsScene() { clearSelection(); }

    void GraphicsScene::appendAction(UndoAction* undoAction) {}

    void GraphicsScene::drawForeground(QPainter* painter, const QRectF& rect)
    {
        QGraphicsScene::drawForeground(painter, rect);

        if (const auto tool = m_graphicsToolManager->currentGraphicsTool()) {
            tool->drawForeground(painter, rect);
        }
    }

    void GraphicsScene::drawBackground(QPainter* painter, const QRectF& rect)
    {
        QGraphicsScene::drawBackground(painter, rect);
        painter->fillRect(sceneRect(), Qt::darkGray);
    }

    void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        if (const auto tool = m_graphicsToolManager->currentGraphicsTool()) {
            if (tool->mousePressEvent(event)) {
                QGraphicsScene::mousePressEvent(event);
            }
        }
        update();
    }

    void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
    {
        if (const auto tool = m_graphicsToolManager->currentGraphicsTool()) {
            if (tool->mouseMoveEvent(event)) {
                QGraphicsScene::mouseMoveEvent(event);
            }
        }
    }

    void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
    {
        if (const auto tool = m_graphicsToolManager->currentGraphicsTool()) {
            if (tool->mouseReleaseEvent(event)) {
                QGraphicsScene::mouseReleaseEvent(event);
            }
        }
        update();
    }

    void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
    {
        if (const auto tool = m_graphicsToolManager->currentGraphicsTool()) {
            if (tool->mouseDoubleClickEvent(event)) {
                QGraphicsScene::mouseDoubleClickEvent(event);
            }
        }
        update();
    }

    void GraphicsScene::keyPressEvent(QKeyEvent* event)
    {
        if (const auto tool = m_graphicsToolManager->currentGraphicsTool()) {
            if (tool->keyPressEvent(event)) {
                QGraphicsScene::keyPressEvent(event);
            }
        }
        update();
    }

    void GraphicsScene::keyReleaseEvent(QKeyEvent* event)
    {
        if (const auto tool = m_graphicsToolManager->currentGraphicsTool()) {
            if (tool->keyReleaseEvent(event)) {
                QGraphicsScene::keyReleaseEvent(event);
            }
        }
    }

    void GraphicsScene::wheelEvent(QGraphicsSceneWheelEvent* event) { QGraphicsScene::wheelEvent(event); }

    void GraphicsScene::setupInteractionModeManager() {}

    void GraphicsScene::setupGraphicsToolManager() {}

    void GraphicsScene::onSelectionChanged()
    {
        const QList<QGraphicsItem*> items = selectedItems();
        m_selectedItemsBoundingBox.update(items);
        update();
    }
} // namespace Mesia
