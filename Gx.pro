TEMPLATE = lib
CONFIG += console
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

DEFINES -= UNICODE

QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_LFLAGS += -Wl,--exclude-all-symbols

QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas -Wno-comment -Wno-maybe-uninitialized -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-attributes -Wno-strict-aliasing

INCLUDEPATH += "C:/Projects/pcx" \
               "C:/lib/Bullet/src"

PRE_TARGETDEPS += "C:/Projects/pcx/build-pcx/release/libpcx.a"

LIBS += "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3d9.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/d3dx9.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/dxerr.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/dsound.lib" \
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64/dxguid.lib" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libuser32.a" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libgdi32.a" \
        "C:/mingw64/x86_64-w64-mingw32.shared/lib/libpsapi.a" \
        "C:/Projects/pcx/build-pcx/release/libpcx.a" \
        "C:/lib/Bullet/build-Bullet/release/libBullet.a"

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
    GxGraphics/GxExclusiveGraphicsDevice.cpp \
    GxMaths/GxVector.cpp \
    GxMaths/GxQuaternion.cpp \
    GxMaths/GxRay.cpp \
    GxMaths/GxTransform.cpp \
    GxMaths/GxViewport.cpp \
    GxAudio/GxAudioBuffer.cpp \
    GxAudio/GxAudioDevice.cpp \
    internal/gx_audio_common.cpp \
    GxPhysics/GxPhysicsModel.cpp \
    internal/gx_physics_gjk.cpp \
    GxPhysics/GxPhysicsTypes.cpp \
    internal/gx_physics_common.cpp \
    GxPhysics/GxShapes/GxShape.cpp \
    GxPhysics/GxShapes/GxCapsuleShape.cpp \
    GxPhysics/GxShapes/GxSphereShape.cpp \
    GxPhysics/GxShapes/GxPolyhedronShape.cpp \
    GxPhysics/GxBody.cpp \
    GxMaths/GxAabb.cpp \
    internal/gx_physics_broadphase.cpp \
    internal/gx_physics_ray.cpp \
    GxMaths/GxRect.cpp \
    GxPhysics/GxShapes/GxConeShape.cpp

HEADERS += \
    GxApplication/GxApplication.h \
    GxGraphics/GxGraphicsDevice.h \
    GxCore/GxDebug.h \
    GxCore/GxTimer.h \
    GxCore/GxWindows.h \
    GxMaths/GxSize.h \
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
    GxGraphics/GxGraphicsTypes.h \
    GxGraphics/GxExclusiveGraphicsDevice.h \
    GxMaths/GxQuaternion.h \
    GxMaths/GxRay.h \
    GxGraphics/GxBufferStream.h \
    GxMaths/GxTransform.h \
    GxMaths/GxRange.h \
    GxMaths/GxViewport.h \
    GxAudio/GxAudioBuffer.h \
    GxAudio/GxAudioDevice.h \
    GxAudio/GxAudioTypes.h \
    internal/gx_audio_common.h \
    GxPhysics/GxPhysicsModel.h \
    internal/gx_physics_gjk.h \
    GxPhysics/GxPhysicsTypes.h \
    internal/gx_physics_common.h \
    GxPhysics/GxShapes/GxShape.h \
    GxPhysics/GxShapes/GxCapsuleShape.h \
    GxPhysics/GxShapes/GxSphereShape.h \
    GxPhysics/GxShapes/GxPolyhedronShape.h \
    GxPhysics/GxBody.h \
    GxMaths/GxAabb.h \
    internal/gx_physics_broadphase.h \
    internal/gx_physics_ray.h \
    GxMaths/GxBlendValue.h \
    GxMaths/GxRect.h \
    GxMaths/GxPoint.h \
    GxPhysics/GxShapes/GxConeShape.h

