#include "speaker.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <alc.h>
#include <al.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#include "alut.h"

sound_t *sound_new()
{
	ALCenum error;

	sound_t *self = malloc(sizeof(self));

	alGenBuffers((ALuint)1, &self->buffer);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);

	return self;
}

float sound_get_value(sound_t *self, int32_t offset)
{
	uint8_t *data = self->data;
	switch (self->format)
	{
		case AL_FORMAT_MONO16:
			return ((float)*((int16_t*)&data[offset])) / SHRT_MAX;
		case AL_FORMAT_MONO8:
			return ((float)*((int8_t*)&data[offset])) / CHAR_MAX;
		case AL_FORMAT_STEREO16:
			return ((float)*((int16_t*)&data[offset])) / SHRT_MAX;
		case AL_FORMAT_STEREO8:
			return ((float)*((int8_t*)&data[offset])) / CHAR_MAX;
	}
	return 0.0f;
}

int sound_load(sound_t *self, const char *filename)
{
	ALCenum error;
	self->data = alutLoadMemoryFromFile(filename, &self->format, &self->size,
			&self->freq);
	alBufferData(self->buffer, self->format, self->data, self->size, self->freq);

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

