#ifndef BLENDMODE_H
#define BLENDMODE_H

// Defines various blending modes for combining layers in a scene
enum class lsBlendMode {
    ADD,
    SUBTRACT,
    MULTIPLY,
    FUSE_UP,    // New blend mode using |= operator for 'fusing' colors upwards
    FUSE_DOWN,  // New blend mode using &= operator for 'fusing' colors downwards
    N_BLEND,    // New blend mode using FastLED's nblend method for smooth blending
    // Additional blend modes can be added here
};

#endif // BLENDMODE_H