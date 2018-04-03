#include <QApplication>
#include "designercore.h"
#include "console.h"
#include "reportcore.h"
#include "log.h"


#ifdef STATICPLUGINS_DESIGNER
    #include "designer_static.h"
    #ifdef EXTENDEDSUITE
    #include "designer_staticExt.h"
    #endif
#endif

#ifdef STATICPLUGINS_PROPERTYEDITOR
#include "propertyeditor_static.h"
#endif

#ifdef STATICPLUGINS_CORE
    #include "core_static.h"
    #ifdef EXTENDEDSUITE
    #include "core_staticExt.h"
    #endif
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //load skin file.
    QFile skinFile(":/skin/DefaultUI.qss");
    if(skinFile.open(QIODevice::ReadOnly))
    {
        QString qss=skinFile.readAll();
        app.setStyleSheet(qss);
        skinFile.close();
    }

    bool designer = true;
//    for (int i=0; i< argc; ++i) {
//        if (QString(argv[i]) == "-g")
//            designer = true;
//    }

    if (designer) {
        CuteDesigner::Core  * core = new CuteDesigner::Core();
        int result = app.exec();
        delete core;
        return result;
    } else {
        Console console;
        console.run(argc, argv);
        return app.exec();
    }

    return -1;
}
