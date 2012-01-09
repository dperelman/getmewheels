#include "mapwidget.h"
#include "core.h"
#include "engines/car2go/car2goengine.h"
#include "settings.h"

#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QtDeclarative>

Q_IMPORT_PLUGIN(qtgeoservices_osm)

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    qmlRegisterType<MapWidget>("GetMeWheels", 1, 0, "GmwMap");
    qmlRegisterType<GMWItemModel>("GetMeWheels", 1, 0, "GmwModel");
    qmlRegisterType<GMWItem>();
    qmlRegisterUncreatableType<GMWItem>("GetMeWheels", 1, 0, "GmwItem", "Cannot create items of type GmwItem");
    qmlRegisterUncreatableType<GMWVehicle>("GetMeWheels", 1, 0, "GmwVehicle", "Cannot create items of type GmwVehicle");
    qmlRegisterType<GMWBooking>();

    qmlRegisterType<GMWEngine>();
    qmlRegisterType<Car2goEngine>("GetMeWheels", 1, 0, "Car2goEngine");

    Settings settings;
    qmlRegisterType<Settings>("GetMeWheels", 1, 0, "Settings");
    viewer->rootContext()->setContextProperty("gmwSettings", &settings);

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/getmewheels2/main.qml"));
    viewer->showExpanded();

    return app->exec();
}
