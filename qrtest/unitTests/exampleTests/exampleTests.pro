TARGET = exampleTests

include(../common.pri)

LIBS += -L../../../bin -lqrkernel -lqrutils

include(../../../plugins/blockDiagram/visualDebugSupport/interpreter/interpreter.pri)

HEADERS += \
	sampleFixtureTest.h \
	testClass.h \
	mockedTestClass.h \

SOURCES += \
	sampleTest.cpp \
	sampleFixtureTest.cpp \
	mockTest.cpp \
