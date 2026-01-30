#if !defined(WIN32_HANDMADE_H)
/* ===================================================================
    $File: $
    $Date: $
    $Revision: $
    $Creator: Beau Taapken $
    $Notice: (C) Copyright 2024 by Beau Taapken. All Rights Reserved. $
    =================================================================== */

#include "common/typedefs.h"

struct win32_offscreen_buffer {
    // NOTE: Pixels are always 32-bits wide, Memory Order  0x BB GG RR xx
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
    int BytesPerPixel;
};

struct win32_window_dimension {
    int Width;
    int Height;
};

struct win32_sound_output {
    // NOTE: Sound test
    int SamplesPerSecond;
    uint32 RunningSampleIndex;
    int BytesPerSample;
    DWORD SecondaryBufferSize;
    DWORD SafetyBytes;
    float tSine;
    int LatencySampleCount;
    // TODO: Should running sample index be in bytes as well?
    // TODO: Math gets simpler if we add a "bytes per second" field?
};

struct win32_debug_time_marker {
    DWORD OutputPlayCursor;
    DWORD OutputWriteCursor;
    DWORD OutputLocation;
    DWORD OutputByteCount;
    DWORD ExpectedFlipPlayCursor;

    DWORD FlipPlayCursor;
    DWORD FlipWriteCursor;
};

struct win32_game_code {
    HMODULE GameCodeDLL;
    FILETIME DLLLastWriteTime;
    game_update_and_render *UpdateAndRender;
    game_get_sound_samples *GetSoundSamples;

    bool IsValid;
};

#define WIN32_HANDMADE_H
#endif
