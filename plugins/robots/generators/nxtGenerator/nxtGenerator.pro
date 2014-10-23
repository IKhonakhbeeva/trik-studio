QT += widgets

CONFIG += c++11

TEMPLATE = lib
CONFIG += plugin

DESTDIR = ../../../../bin/plugins/tools/kitPlugins/
TARGET = robots-nxt-generator

MOC_DIR = .moc
RCC_DIR = .moc
OBJECTS_DIR = .obj

LIBS += -L../../../../bin -lqrkernel -lqslog -lqrutils -lqrrepo -lrobots-generator-base

INCLUDEPATH += \
	$$PWD/../generatorBase/include/ \
	$$PWD/../../interpreters/interpreterBase/include \
	$$PWD/../../../../ \
	$$PWD/../../../../qrgui \
	$$PWD/../../../../qrtext/include \

# workaround for http://bugreports.qt.nokia.com/browse/QTBUG-8110
# when fixed it would become possible to use QMAKE_LFLAGS_RPATH
!macx {
	QMAKE_LFLAGS += -Wl,-O1,-rpath,$$PWD/../../../bin/
	QMAKE_LFLAGS += -Wl,-rpath,$$PWD/../../../bin/plugins/
}

TRANSLATIONS = $$PWD/../../../../qrtranslations/ru/plugins/robots/nxtGenerator_ru.ts

RESOURCES = \
	$$PWD/nxtGenerator.qrc \
	$$PWD/templates.qrc \

HEADERS += \
	$$PWD/nxtGeneratorPlugin.h \
	$$PWD/nxtFlashTool.h \
	$$PWD/nxtOsekMasterGenerator.h \
	$$PWD/nxtOsekGeneratorCustomizer.h \
	$$PWD/nxtOsekGeneratorFactory.h \
	$$PWD/converters/nxtStringPropertyConverter.h \

SOURCES += \
	$$PWD/nxtGeneratorPlugin.cpp \
	$$PWD/nxtFlashTool.cpp \
	$$PWD/nxtOsekMasterGenerator.cpp \
	$$PWD/nxtOsekGeneratorCustomizer.cpp \
	$$PWD/nxtOsekGeneratorFactory.cpp \
	$$PWD/converters/nxtStringPropertyConverter.cpp \
