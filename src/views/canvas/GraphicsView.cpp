#include <QDebug>
#include <QGraphicsPathItem>
#include <QScrollBar>
#include <QWheelEvent>
#include "GraphicsScene.hpp"
#include "GraphicsView.hpp"

namespace Mesia {
    GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {
        setMouseTracking(true);
        setRenderHint(QPainter::Antialiasing);
        setCacheMode(CacheBackground);
        setOptimizationFlags(DontSavePainterState);
        setViewportUpdateMode(SmartViewportUpdate);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    void GraphicsView::wheelEvent(QWheelEvent *event) {
        QGraphicsView::wheelEvent(event);

        qreal factor;
        if (event->angleDelta().y() > 0) {
            factor = 1.2;
        } else {
            factor = 1.0 / 1.2;
        }
        QTransform viewTransform = transform();
        viewTransform.translate(event->position().x(), event->position().y());
        viewTransform.scale(factor, factor);
        viewTransform.translate(-event->position().x(), -event->position().y());
        setTransform(viewTransform);
    }

    void GraphicsView::resizeEvent(QResizeEvent *event) {
//        int w = event->size().width();
//        int h = event->size().height();
//        setSceneRect(-w * 0.5, -h * 0.5, w, h);
        QGraphicsView::resizeEvent(event);
    }

    void GraphicsView::mousePressEvent(QMouseEvent *event) {
        qDebug() << mapToScene(event->pos());
        QGraphicsView::mousePressEvent(event);
    }

    void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
        QGraphicsView::mouseMoveEvent(event);
    }

    void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {
        QGraphicsView::mouseReleaseEvent(event);
    }

    void GraphicsView::drawForeground(QPainter* painter, const QRectF& rect) {
        QGraphicsView::drawForeground(painter, rect);
    }
}
