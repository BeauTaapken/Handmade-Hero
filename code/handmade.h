#if !defined(HANDMADE_H)
/* ===================================================================
    $File: $
    $Date: $
    $Revision: $
    $Creator: Beau Taapken $
    $Notice: (C) Copyright 2024 by Beau Taapken. All Rights Reserved. $
    =================================================================== */

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
// TODO: swap, min, max ... macros???

/*
    TODO: Services that the platform layer provides to the game
*/

/*
    NOTE: Services that the game provides to the platform layer.
    (this may expand in the future - sound on separate thread, etc.)
*/

// FOUR THINGS - timing, controller/keyboard input, bitmap buffer to use, sound buffer to use
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
    bool IsAnalog;

    float StartX;
    float StartY;

    float MinX;
    float MinY;

    float MaxX;
    float MaxY;

    float EndX;
    float EndY;

    union {
        game_button_state Buttons[6];
        struct {
            game_button_state Up;
            game_button_state Down;
            game_button_state Left;
            game_button_state Right;
            game_button_state LeftShoulder;
            game_button_state RightShoulder;
        };
    };
};

struct game_input {
    game_controller_input Controllers[4];
};

internal void GameUpdateAndRender(game_input *Input, game_offscreen_buffer *Buffer, game_sound_output_buffer *SoundBuffer);

#define HANDMADE_H
#endif
