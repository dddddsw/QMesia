#include "app/Application.hpp"
#include <QIntValidator>

int main(int argc, char *argv[]) {
    Mesia::Application app(argc, argv);

    QIntValidator validator;
    validator.setRange(10, 1000);

    QString str = "4000";
    int num = -1;
    qDebug() << validator.validate(str, num) << str << num;

    return app.run();
}
