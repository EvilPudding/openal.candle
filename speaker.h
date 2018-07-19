#ifndef SPEAKER_H
#define SPEAKER_H

#include <ecm.h>
#include "sound.h"

typedef struct c_speaker_t
{
	c_t super;
	unsigned int source;
} c_speaker_t;

DEF_CASTER("speaker", c_speaker, c_speaker_t)

c_speaker_t *c_speaker_new(void);

void c_speaker_play(c_speaker_t *self, sound_t *sound, int loop);

#endif /* !SPEAKER_H */
