// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"
#include "core/hw/gpu.h"

struct ScreenInfo;

namespace Pica {
namespace Shader {
struct OutputVertex;
}
}

namespace VideoCore {

class RasterizerInterface {
public:
    virtual ~RasterizerInterface() {}

    /// Queues the primitive formed by the given vertices for rendering
    virtual void AddTriangle(const Pica::Shader::OutputVertex& v0,
                             const Pica::Shader::OutputVertex& v1,
                             const Pica::Shader::OutputVertex& v2) = 0;

    /// Draw the current batch of triangles
    virtual void DrawTriangles() = 0;

    /// Notify rasterizer that the specified PICA register has been changed
    virtual void NotifyPicaRegisterChanged(u32 id) = 0;

    /// Notify rasterizer that all caches should be flushed to 3DS memory
    virtual void FlushAll() = 0;

    /// Notify rasterizer that any caches of the specified region should be flushed to 3DS memory
    virtual void FlushRegion(PAddr addr, u32 size) = 0;

    /// Notify rasterizer that any caches of the specified region should be flushed to 3DS memory
    /// and invalidated
    virtual void FlushAndInvalidateRegion(PAddr addr, u32 size) = 0;

    /// Attempt to use a faster method to perform a display transfer
    virtual bool AccelerateDisplayTransfer(const GPU::Regs::DisplayTransferConfig& config) {
        return false;
    }

    /// Attempt to use a faster method to fill a region
    virtual bool AccelerateFill(const GPU::Regs::MemoryFillConfig& config) {
        return false;
    }

    /// Attempt to use a faster method to display the framebuffer to screen
    virtual bool AccelerateDisplay(const GPU::Regs::FramebufferConfig& config,
                                   PAddr framebuffer_addr, u32 pixel_stride,
                                   ScreenInfo& screen_info) {
        return false;
    }
};
}
