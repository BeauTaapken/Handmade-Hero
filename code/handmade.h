#if !defined(HANDMADE_H)
/* ===================================================================
    $File: $
    $Date: $
    $Revision: $
    $Creator: Beau Taapken $
    $Notice: (C) Copyright 2024 by Beau Taapken. All Rights Reserved. $
    =================================================================== */

#include "common/typedefs.h"

/*
  NOTE:

  HANDMADE_INTERNAL:
    0 - Build for public release
    1 - Build for developer only

  HANDMADE_SLOW:
    0 - No slow code allowed!
    1 - Slow code allowed.
 */

#if HANDMADE_SLOW
#define Assert(Expression)                                                                                                                 \
    if (!(Expression)) {                                                                                                                   \
        *static_cast<int *>(0) = 0;                                                                                                        \
    }
#else
#define Assert(Expression)
#endif

// TODO: Should these always use 64-bit?
#define Kilobytes(Value) ((Value) * 1024)
#define Megabytes(Value) (Kilobytes(Value) * 1024)
#define Gigabytes(Value) (Megabytes(Value) * 1024)
#define Terabytes(Value) (Gigabytes(Value) * 1024)

#define ArrayCount(Array) static_cast<int>(sizeof(Array) / sizeof((Array)[0]))
// TODO: swap, min, max ... macros???

inline uint32 SafeTruncateUInt64(uint64 Value) {
    Assert(Value <= 0xFFFFFFFF);
    uint32 Result = static_cast<uint32>(Value);
    return (Result);
}

/*
   NOTE: Services that the platform layer provides to the game
*/
#if HANDMADE_INTERNAL
/*
    NOTE:
 */
struct debug_read_file_result {
    uint32 ContentsSize;
    void *Contents;
};
internal debug_read_file_result DEBUGPlatformReadEntireFile(char *Filename);
internal void DEBUGPlatformFreeFileMemory(void *Memory);
internal bool DEBUGPlatformWriteEntireFile(char *Filename, uint32 MemorySize, void *Memory);
#endif

/*
    NOTE: Services that the game provides to the platform layer.
    (this may expand in the future - sound on separate thread, etc.)
*/

// FOUR THINGS - timing, controller/keyboard input, bitmap buffer to use, sound
// buffer to use
struct game_offscreen_buffer {
    // NOTE: Pixels are always 32-bits wide, Memory Order  0x BB GG RR xx
    void *Memory;
    int Width;
    int Height;
    int Pitch;
};

struct game_sound_output_buffer {
    int SamplesPerSecond;
    int SampleCount;
    int16 *Samples;
};

struct game_button_state {
    int HalfTransitionCount;
    bool EndedDown;
};

struct game_controller_input {
    bool IsConnected;
    bool IsAnalog;
    float StickAverageX;
    float StickAverageY;

    union {
        game_button_state Buttons[12];
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
        struct {
#pragma GCC diagnostic pop
            game_button_state MoveUp;
            game_button_state MoveDown;
            game_button_state MoveLeft;
            game_button_state MoveRight;

            game_button_state ActionUp;
            game_button_state ActionDown;
            game_button_state ActionLeft;
            game_button_state ActionRight;

            game_button_state LeftShoulder;
            game_button_state RightShoulder;

            game_button_state Back;
            game_button_state Start;

            // NOTE: All buttons must be added above this line

            game_button_state Terminator;
        };
    };
};

struct game_input {
    // TODO: Insert clock value here.
    game_controller_input Controllers[5];
};
inline game_controller_input *GetController(game_input *Input, int unsigned ControllerIndex) {
    Assert(ControllerIndex < static_cast<int>(ArrayCount(Input->Controllers)));
    game_controller_input *Result = &Input->Controllers[ControllerIndex];
    return (Result);
}

struct game_memory {
    bool IsInitialized;
    uint64 PermanentStorageSize;
    void *PermanentStorage; // NOTE: REQUIRED to be cleared to zero at startup
    uint64 TransientStorageSize;
    void *TransientStorage; // NOTE: REQUIRED to be cleared to zero at startup
};

internal void GameUpdateAndRender(game_memory *Memory, game_input *Input, game_offscreen_buffer *Buffer);

// Note: At the moment, this has to be a very fast function, it cannot be more than a millisecond or so.
// TODO: Reduce the pressure on this function's performance by measuring it or asking about it, etc.
internal void GameGetSoundSamples(game_memory *Memory, game_sound_output_buffer *SoundBuffer);

//
//
//

struct game_state {
    int ToneHz;
    int GreenOffset;
    int BlueOffset;
};

#define HANDMADE_H
#endif
