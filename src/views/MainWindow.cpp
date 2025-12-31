#include "canvas/GraphicsScene.hpp"
#include "canvas/GraphicsView.hpp"
#include "canvas/tools/GraphicsToolManager.hpp"
#include "MainWindow.hpp"

namespace Mesia {
    MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                                m_graphicsView(new GraphicsView(this)),
                                                m_graphicsScene(new GraphicsScene(this)) {
        setupComponents();
    }

    void MainWindow::setupComponents() {
        m_graphicsScene->setGraphicsToolManager(new GraphicsToolManager(m_graphicsView, m_graphicsScene));
        m_graphicsScene->setView(m_graphicsView);

        m_graphicsView->setScene(m_graphicsScene);
        setCentralWidget(m_graphicsView);
    }
}