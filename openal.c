#include "openal.h"
#include "sound.h"

#include <systems/sauces.h>
#include <components/camera.h>
#include <components/node.h>

#include <stdio.h>
#include <stdlib.h>

#include <alc.h>
#include <al.h>
#include "alut.h"

//static LPALCGETSTRINGISOFT alcGetStringiSOFT;
//static LPALCRESETDEVICESOFT alcResetDeviceSOFT;

void *sound_loader(const char *path, const char *name, uint32_t ext)
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
	alutInitWithoutContext(0, NULL);

	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

	sauces_loader(ref("wav"), sound_loader);
}

void c_openal_set_listener(c_openal_t *self, entity_t listener)
{
	self->listener = listener;
}

int c_openal_update(c_openal_t *self)
{
	if(!entity_exists(self->listener)) return CONTINUE;
	c_node_t *nc = c_node(&self->listener);
	if(!nc) return CONTINUE;

	vec3_t pos = c_node_local_to_global(nc, Z3);
	vec3_t at = c_node_dir_to_global(nc, vec3(0.0f, 0.0f, -1.0f));
	vec3_t up = c_node_dir_to_global(nc, vec3(0.0f, 1.0f, 0.0f));

	ALfloat listenerOri[] = { at.x, at.y, at.z, up.x, up.y, up.z };
	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alListener3f(AL_VELOCITY, 0, 0, 0);

	ALCenum error;
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);

	return CONTINUE;
}

c_openal_t *c_openal_new()
{

	c_openal_t *self = component_new("openal");

	c_openal_update(self);

	return self;
}

void c_openal_destroy(c_openal_t *self)
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(self->context);
	alcCloseDevice(self->device);
}

REG()
{
	ct_t *ct = ct_new("openal", sizeof(c_openal_t), c_openal_init,
			c_openal_destroy, 0);

	ct_listener(ct, WORLD, sig("world_update"), c_openal_update);
}

