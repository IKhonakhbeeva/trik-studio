TARGET = quazip
TEMPLATE = lib

include (../../global.pri)

QMAKE_CXXFLAGS += -Wno-error=non-virtual-dtor -Wno-error=cast-qual
DEFINES += QUAZIP_BUILD

include (quazip/quazip/quazip.pri)
