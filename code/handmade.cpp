/* ===================================================================
    $File: $
    $Date: $
    $Revision: $
    $Creator: Beau Taapken $
    $Notice: (C) Copyright 2024 by Beau Taapken. All Rights Reserved. $
    =================================================================== */

#include "handmade.h"

internal void GameOutputSound(game_sound_output_buffer *SoundBuffer, int ToneHz) {
    local_persist float tSine;
    int16 ToneVolume = 1000;
    int WavePeriod = SoundBuffer->SamplesPerSecond / ToneHz;

    int16 *SampleOut = SoundBuffer->Samples;
    for (int SampleIndex = 0; SampleIndex < SoundBuffer->SampleCount; ++SampleIndex) {
        float SineValue = sinf(tSine);
        int16 SampleValue = static_cast<int16>(SineValue * ToneVolume);
        *SampleOut++ = SampleValue;
        *SampleOut++ = SampleValue;

        tSine += 2.0f * Pi * 1.0f / static_cast<float>(WavePeriod);
        if (tSine > 2.0f * Pi) {
            tSine -= 2.0f * Pi;
        }
    }
}

internal void RenderWeirdGradient(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset) {
    // TODO: Let's see what the optimizer does
    uint8 *Row = static_cast<uint8 *>(Buffer->Memory);
    for (int Y = 0; Y < Buffer->Height; Y++) {
        uint32 *Pixel = reinterpret_cast<uint32 *>(Row);
        for (int X = 0; X < Buffer->Width; X++) {
            uint8 Blue = static_cast<uint8>(X + BlueOffset);
            uint8 Green = static_cast<uint8>(Y + GreenOffset);

            *Pixel++ = ((Green << 8) | Blue);
        }

        Row += Buffer->Pitch;
    }
}

internal void GameUpdateAndRender(game_memory *Memory, game_input *Input, game_offscreen_buffer *Buffer) {
    Assert((&Input->Controllers[0].Start - &Input->Controllers[0].Buttons[0]) == (ArrayCount(Input->Controllers[0].Buttons) - 1));
    Assert(sizeof(game_state) <= Memory->PermanentStorageSize);

    game_state *GameState = static_cast<game_state *>(Memory->PermanentStorage);

    if (!Memory->IsInitialized) {
        debug_read_file_result File = DEBUGPlatformReadEntireFile(const_cast<char *>("../code/handmade.cpp"));
        if (File.Contents) {
            DEBUGPlatformWriteEntireFile(const_cast<char *>("../data/test.out"), File.ContentsSize, File.Contents);
            DEBUGPlatformFreeFileMemory(File.Contents);
        }
        GameState->ToneHz = 512;

        // TODO: This may be more appropriate to do in the platform layer
        Memory->IsInitialized = true;
    }

    for (int ControllerIndex = 0; ControllerIndex < ArrayCount(Input->Controllers); ++ControllerIndex) {
        game_controller_input *Controller = GetController(Input, ControllerIndex);
        if (Controller->IsAnalog) {
            // NOTE: Use analog movement tuning
            GameState->BlueOffset += static_cast<int>(4.0f * (Controller->StickAverageX));
            GameState->ToneHz = 512 + static_cast<int>(128.0f * (Controller->StickAverageY));
        } else {
            // NOTE: Use digital movement tuning
            if (Controller->MoveLeft.EndedDown) {
                GameState->BlueOffset -= 1;
            }
            if (Controller->MoveRight.EndedDown) {
                GameState->BlueOffset += 1;
            }
        }

        if (Controller->ActionDown.EndedDown) {
            GameState->GreenOffset += 1;
        }
    }

    RenderWeirdGradient(Buffer, GameState->BlueOffset, GameState->GreenOffset);
}

internal void GameGetSoundSamples(game_memory *Memory, game_sound_output_buffer *SoundBuffer) {
    game_state *GameState = static_cast<game_state *>(Memory->PermanentStorage);
    GameOutputSound(SoundBuffer, GameState->ToneHz);
}
