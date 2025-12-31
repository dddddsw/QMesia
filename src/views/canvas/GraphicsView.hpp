#ifndef MESIA_GRAPHICS_VIEW_H
#define MESIA_GRAPHICS_VIEW_H

#include <QGraphicsView>

namespace Mesia {
    class GraphicsView : public QGraphicsView {
        Q_OBJECT
    public:
        explicit GraphicsView(QWidget *parent);

    protected:
        void wheelEvent(QWheelEvent *event) override;
        void resizeEvent(QResizeEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

        void drawForeground(QPainter* painter, const QRectF& rect) override;
    };
}

#endif
