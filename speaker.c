#include "speaker.h"
#include <components/node.h>

#include <stdio.h>
#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#define FILENAME "resauces/0.wav"

static int c_speaker_update_position(c_speaker_t *self);

void c_speaker_init(c_speaker_t *self)
{

	alGenSources((ALuint)1, &self->source);
	ALCenum error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
	c_speaker_update_position(self);
}

void c_speaker_set_gain(c_speaker_t *self, float gain)
{
	alSourcef(self->source, AL_GAIN, gain);
	ALCenum error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
}

void c_speaker_set_pitch(c_speaker_t *self, float pitch)
{
	alSourcef(self->source, AL_PITCH, 1);
	ALCenum error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
}

static int c_speaker_update_position(c_speaker_t *self)
{
	c_node_t *nc = c_node(self);
	c_node_update_model(nc);
	vec3_t p = c_node_local_to_global(nc, vec3(0, 0, 0));

	alSource3f(self->source, AL_POSITION, p.x, p.y, p.z);
	ALCenum error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
	/* alSource3f(source, AL_VELOCITY, 0, 0, 0); */
	/* error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__); */
	return CONTINUE;
}

void c_speaker_play(c_speaker_t *self, sound_t *sound, int loop)
{
	ALCenum error;

	alSourcei(self->source, AL_LOOPING, loop);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);

	alSourcei(self->source, AL_BUFFER, sound->buffer);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);

	alSourcePlay(self->source);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
}

c_speaker_t *c_speaker_new()
{
	c_speaker_t *self = component_new("speaker");

	return self;
}

c_speaker_t *c_speaker_destroy(c_speaker_t *self)
{
	alDeleteSources(1, &self->source);
}

REG()
{
	ct_t *ct = ct_new("speaker", sizeof(c_speaker_t), c_speaker_init, c_speaker_destroy, 1,
			ref("node"));
	ct_listener(ct, ENTITY, sig("spacial_changed"), c_speaker_update_position);
}

