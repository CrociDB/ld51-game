#include "defs.h"
#include "audio.h"

#include "wasm4.h"

void audio_play_tone(
    uint16_t freq1, 
    uint16_t freq2, 
    uint8_t attack, 
    uint8_t decay, 
    uint8_t sustain, 
    uint8_t release,
    uint8_t peak,
    uint8_t volume,
    uint8_t channel,
    uint8_t mode,
    uint8_t pan)
{
    tone(
        (uint32_t)(freq1 | (freq2 << 16)), 
        (uint32_t)((attack << 24) | (decay << 16) | sustain | (release << 8)), 
        (uint32_t)((peak << 8) | volume), 
        (uint32_t)(channel | (mode << 2) | (pan << 4)));
}

void audio_play_shoot()
{
    uint16_t freq1 = (uint16_t)(580 + frandom() * 300);
    uint8_t volume = (uint8_t)(6 + frandom() * 5);
    
    audio_play_tone(freq1, 60, 0, 0, 3, 0, 11, volume, 0, TONE_PULSE1, TONE_PAN_LEFT | TONE_PAN_RIGHT);
}

void audio_play_crash()
{
    uint16_t freq1 = (uint16_t)(60 + frandom() * 50);
    
    audio_play_tone(freq1, 10, 0, 8, 2, 16, 3, 7, 3, TONE_PULSE2, TONE_PAN_LEFT | TONE_PAN_RIGHT);
}

void audio_play_hit_enemy()
{
    uint16_t freq1 = (uint16_t)(70 + frandom() * 70);
    
    audio_play_tone(freq1, 30, 2, 0, 2, 125, 25, 7, 3, TONE_PULSE2, TONE_PAN_LEFT | TONE_PAN_RIGHT);
}
