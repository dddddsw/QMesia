#pragma once

#ifndef MESIA_APPLICATION_HPP
#define MESIA_APPLICATION_HPP

#include <QApplication>

namespace Mesia {
    class MainWindow;
    class Application : public QApplication {
        Q_OBJECT
    public:
        Application(int argc, char **argv);
        ~Application() override;

        int run();

    private:
        QScopedPointer<MainWindow> m_mainWindow;
    };
}

#endif
