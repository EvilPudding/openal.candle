#ifndef SPEAKER_H
#define SPEAKER_H

#include <ecs/ecm.h>
#include "sound.h"
#include <utils/drawable.h>

typedef struct c_speaker_t
{
	c_t super;
	uint32_t source;
	drawable_t draw;
	sound_t *playing;
} c_speaker_t;

void ct_speaker(ct_t *self);
DEF_CASTER(ct_speaker, c_speaker, c_speaker_t)

c_speaker_t *c_speaker_new(void);

void c_speaker_play(c_speaker_t *self, sound_t *sound, bool_t loop);
int32_t c_speaker_get_byte_offset(c_speaker_t *self);

#endif /* !SPEAKER_H */
