#include "views/MainWindow.hpp"
#include "Application.hpp"

namespace Mesia {
    Application::Application(int argc, char **argv) : QApplication(argc, argv) {

    }

    Application::~Application() {
    }

    int Application::run() {
        m_mainWindow.reset(new MainWindow);
        m_mainWindow->resize(1024, 768);
        m_mainWindow->show();
        return exec();
    }
} // Mesia