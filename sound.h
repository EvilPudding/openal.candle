#ifndef SOUND_H
#define SOUND_H

#include "../candle/ecs/ecm.h"

typedef struct
{
	uint32_t buffer;
	int32_t size;
	int32_t freq;
	uint32_t format;
	void *data;
} sound_t;

sound_t *sound_new(void);

int sound_load(sound_t *self, const char *bytes, size_t bytes_num);
float sound_get_value(sound_t *self, int32_t offset);

void sound_destroy(sound_t *self);

#endif /* !SOUND_H */
