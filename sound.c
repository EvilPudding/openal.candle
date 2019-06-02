#include "speaker.h"

#include <stdio.h>
#include <stdlib.h>

#include <alc.h>
#include <al.h>
#include "alut.h"

sound_t *sound_new()
{
	ALCenum error;

	sound_t *self = malloc(sizeof(self));

	alGenBuffers((ALuint)1, &self->buffer);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);

	return self;
}

int sound_load(sound_t *self, const char *filename)
{
	ALCenum error;
	self->data = alutLoadMemoryFromFile(filename, &self->format, &self->size,
			&self->freq);

	alBufferData(self->buffer, self->format, self->data, self->size,
			self->freq);

	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		printf("error at %d\n", __LINE__);
		return 0;
	}

	return 1;
}

void sound_destroy(sound_t *self)
{
	alDeleteBuffers(1, &self->buffer);
}

