#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <inttypes.h>

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
    uint8_t pan);

void audio_play_shoot();
void audio_play_crash();
void audio_play_hit_enemy();

#endif
