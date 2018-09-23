TEMPLATE = lib
CONFIG += console
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_LFLAGS += -Wl,--exclude-all-symbols

QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas -Wno-comment -Wno-maybe-uninitialized -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter

INCLUDEPATH += "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"

LIBS += "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3d9.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3dx9.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/dxerr.lib" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libuser32.a" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libgdi32.a" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libpsapi.a"

SOURCES += \
    GxApplication/GxApplication.cpp \
    GxGraphics/GxGraphicsDevice.cpp \
    GxCore/GxDebug.cpp \
    GxCore/GxTimer.cpp \
    GxGraphics/GxVertexDeclaration.cpp \
    GxGraphics/GxVertexBuffer.cpp \
    internal/gx_common.cpp \
    GxGraphics/GxShader.cpp

HEADERS += \
    GxApplication/GxApplication.h \
    GxGraphics/GxGraphicsDevice.h \
    GxCore/GxFlags.h \
    GxCore/GxDebug.h \
    GxCore/GxTimer.h \
    GxCore/GxWindows.h \
    GxCore/GxNonCopyable.h \
    GxCore/GxSize.h \
    GxGraphics/GxDisplaySettings.h \
    GxGraphics/GxGraphicsResource.h \
    GxGraphics/GxVertexDeclaration.h \
    GxCore/GxAlignedStore.h \
    GxGraphics/GxGraphicsCore.h \
    internal/gx_common.h \
    GxGraphics/GxVertexBuffer.h \
    GxGraphics/GxShader.h

