#include "openal.h"
#include "sound.h"

#include <systems/sauces.h>

#include <stdio.h>
#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

void *sound_loader(const char *path, const char *name, uint ext)
{
	sound_t *sound = sound_new();
	sound_load(sound, path);
	return sound;
}


void c_openal_init(c_openal_t *self)
{
	ALCenum error;

	self->device = alcOpenDevice(NULL);
	if(!self->device)
	{
		printf("Could not open al device.\n");
		return;
	}

	self->context = alcCreateContext(self->device, NULL);
	if (!alcMakeContextCurrent(self->context))
	{
		printf("Could not create al context.\n");
		return;
	}
	alutInit(0, NULL);


	sauces_loader(ref("wav"), sound_loader);
}

c_openal_t *c_openal_new()
{
	ALCenum error;

	c_openal_t *self = component_new("openal");

	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
	alListenerfv(AL_ORIENTATION, listenerOri);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);

/* 	ALuint source_state; */
/* 	do */
/* 	{ */
/* 		alGetSourcei(source, AL_SOURCE_STATE, &source_state); */
/* 		error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__); */
/* 	} */
/* 	while (source_state == AL_PLAYING); */

	return self;
}

c_openal_t *c_openal_destroy(c_openal_t *self)
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(self->context);
	alcCloseDevice(self->device);
}

REG()
{
	ct_new("openal", sizeof(c_openal_t), c_openal_init, c_openal_destroy, 0);
}

