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
    int WavePeriod = SoundBuffer->SamplesPerSecond/ToneHz;

    int16 *SampleOut = SoundBuffer->Samples;
    for (int SampleIndex = 0; SampleIndex < SoundBuffer->SampleCount; ++SampleIndex) {
        float SineValue = sinf(tSine);
        int16 SampleValue = (int16)(SineValue * ToneVolume);
        *SampleOut++ = SampleValue;
        *SampleOut++ = SampleValue;

        tSine += 2.0f*Pi32*1.0f / (float)WavePeriod;
    }
}

internal void RenderWeirdGradient(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset){
    // TODO: Let's see what the optimizer does
    uint8 *Row = (uint8 *)Buffer->Memory;
    for(int Y = 0; Y < Buffer->Height; Y++) {
        uint32 *Pixel = (uint32 *)Row;
        for(int X = 0; X < Buffer->Width; X++) {
            uint8 Blue = (X + BlueOffset);
            uint8 Green = (Y + GreenOffset);

            *Pixel++ = ((Green << 8) | Blue);
        }

        Row += Buffer->Pitch;
    }
}

internal void GameUpdateAndRender(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset,
                                  game_sound_output_buffer *SoundBuffer, int ToneHz) {
    // TODO: Allow sample offsets here for more robust platform options
    GameOutputSound(SoundBuffer, ToneHz);
    RenderWeirdGradient(Buffer, BlueOffset, GreenOffset);
};