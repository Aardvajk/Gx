TEMPLATE = lib
CONFIG += console
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_LFLAGS += -Wl,--exclude-all-symbols

QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas -Wno-comment -Wno-maybe-uninitialized -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter

INCLUDEPATH += "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include" \
               "C:/Projects/pcx"

PRE_TARGETDEPS += "C:/Projects/pcx/build-pcx/release/libpcx.a"

LIBS += "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3d9.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3dx9.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/dxerr.lib" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libuser32.a" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libgdi32.a" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libpsapi.a" \
        "C:/Projects/pcx/build-pcx/release/libpcx.a"

SOURCES += \
    GxApplication/GxApplication.cpp \
    GxGraphics/GxGraphicsDevice.cpp \
    GxCore/GxDebug.cpp \
    GxCore/GxTimer.cpp \
    GxGraphics/GxVertexDeclaration.cpp \
    GxGraphics/GxVertexBuffer.cpp \
    GxGraphics/GxShader.cpp \
    GxMaths/GxMatrix.cpp \
    GxGraphics/GxFont.cpp \
    GxGraphics/GxFontMetrics.cpp \
    GxGraphics/GxDepthStencilSurface.cpp \
    GxGraphics/GxTexture.cpp \
    GxGraphics/GxRenderContext.cpp \
    internal/gx_graphics_common.cpp \
    GxGraphics/GxCubeMap.cpp \
    GxGraphics/GxIndexBuffer.cpp

HEADERS += \
    GxApplication/GxApplication.h \
    GxGraphics/GxGraphicsDevice.h \
    GxCore/GxDebug.h \
    GxCore/GxTimer.h \
    GxCore/GxWindows.h \
    GxCore/GxSize.h \
    GxGraphics/GxDisplaySettings.h \
    GxGraphics/GxGraphicsResource.h \
    GxGraphics/GxVertexDeclaration.h \
    GxGraphics/GxVertexBuffer.h \
    GxGraphics/GxShader.h \
    GxMaths/GxMatrix.h \
    GxMaths/GxColor.h \
    GxMaths/GxVector.h \
    GxGraphics/GxFont.h \
    GxGraphics/GxFontMetrics.h \
    GxGraphics/GxDepthStencilSurface.h \
    GxGraphics/GxTexture.h \
    GxGraphics/GxRenderContext.h \
    internal/gx_graphics_common.h \
    internal/gx_common.h \
    GxGraphics/GxCubeMap.h \
    GxGraphics/GxIndexBuffer.h \
    GxGraphics/GxGraphicsTypes.h

