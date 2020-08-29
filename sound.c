#include "openal.h"
#include "speaker.h"

#include <stdio.h>
#include <stdlib.h>

#include "alw.h"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

sound_t *sound_new()
{
	ALCenum error;

	sound_t *self = malloc(sizeof(self));

	alwGenBuffers((ALuint)1, &self->buffer); alerr();

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
	drwav wav;

	if (!drwav_init_memory(&wav, bytes, bytes_num, NULL))
	{
		return 0;
	}

	self->size = (size_t)wav.totalPCMFrameCount * wav.channels * 16;
	self->data = malloc(self->size);
	self->freq = wav.sampleRate;
	if (wav.channels == 2)
	{
		self->format = AL_FORMAT_STEREO16;
	}
	else if (wav.channels == 1)
	{
		self->format = AL_FORMAT_MONO16;
	}
	else
	{
		printf("channels not supported %d\n", wav.channels);
	}

	drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, self->data);
	printf("frequency %d %d %d\n", self->freq, self->size, self->format);
	alwBufferData(self->buffer, self->format, self->data, self->size, self->freq);
	alerr();
	drwav_uninit(&wav);

	return 1;
}

void sound_destroy(sound_t *self)
{
	alwDeleteBuffers(1, &self->buffer);
}

