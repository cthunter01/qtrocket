/// \cond
// C Headers
// C++ Headers
#include <functional>
#include <utility>
// 3rd party headers
#include <QApplication>
#include <QLocale>
#include <QTranslator>
/// \endcond

#include "MainWindow.h"
#include "Logger.h"
#include "RK4Solver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto* logger = Logger::getInstance();
    logger->setLogLevel(Logger::LogLevel::PERF);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "untitled_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    logger->debug("Starting MainWindow");
    MainWindow w;



    w.show();
    return a.exec();
}

void test_RK4()
{

    auto ode = [](double& x, double& r) -> std::pair<double, double>
    {

    }
}
