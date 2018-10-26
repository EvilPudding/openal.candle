#ifndef SOUND_H
#define SOUND_H

#include <ecs/ecm.h>

typedef struct
{
	unsigned int buffer;
	int size;
	float freq;
	int format;
	void *data;
} sound_t;

sound_t *sound_new(void);

int sound_load(sound_t *self, const char *filename);

void sound_destroy(sound_t *self);

#endif /* !SOUND_H */
