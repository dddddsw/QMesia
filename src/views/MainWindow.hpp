#pragma once

#ifndef MESIA_MAIN_WINDOW_HPP
#define MESIA_MAIN_WINDOW_HPP

#include <QMainWindow>

namespace Mesia {
    class GraphicsView;
    class GraphicsScene;
    class MainWindow : public QMainWindow {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        void setupComponents();

    private:
        GraphicsView *m_graphicsView;
        GraphicsScene *m_graphicsScene;
    };
}

#endif
