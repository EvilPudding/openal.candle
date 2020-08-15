#include "openal.h"
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

	alGenBuffers((ALuint)1, &self->buffer); alerr();

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

int sound_load(sound_t *self, const char *bytes, size_t bytes_num)
{
	ALCenum error;
	self->data = alutLoadMemoryFromFileImage(bytes, bytes_num, &self->format,
	                                         &self->size, &self->freq);
	alBufferData(self->buffer, self->format, self->data, self->size, self->freq);
	alerr();

	return 1;
}

void sound_destroy(sound_t *self)
{
	alDeleteBuffers(1, &self->buffer);
}

