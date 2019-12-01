#include "openal.h"
#include "sound.h"

#include <systems/sauces.h>
#include <components/camera.h>
#include <components/node.h>

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
#if !defined(__EMSCRIPTEN__) && !defined(WIN32)
#include <AL/alext.h>
#endif

//static LPALCGETSTRINGISOFT alcGetStringiSOFT;
//static LPALCRESETDEVICESOFT alcResetDeviceSOFT;

#if !defined(__EMSCRIPTEN__) && !defined(WIN32)
static LPALCGETSTRINGISOFT alcGetStringiSOFT;
static LPALCRESETDEVICESOFT alcResetDeviceSOFT;
#endif

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

#ifndef WIN32
#ifndef __EMSCRIPTEN__
	if(!alcIsExtensionPresent(self->device, "ALC_SOFT_HRTF"))
	{
		fprintf(stderr, "Error: ALC_SOFT_HRTF not supported\n");
		exit(1);
	}
#define LOAD_PROC(d, x)  ((x) = alcGetProcAddress((d), #x))
    LOAD_PROC(self->device, alcGetStringiSOFT);
    LOAD_PROC(self->device, alcResetDeviceSOFT);
#undef LOAD_PROC

	/* Enumerate available HRTFs, and reset the device using one. */
	ALCint num_hrtf;
	/* const char *hrtfname = "default-48000"; */
	const char *hrtfname = NULL;
	ALCint hrtf_state;

    alcGetIntegerv(self->device, ALC_NUM_HRTF_SPECIFIERS_SOFT, 1, &num_hrtf);

    if(!num_hrtf) printf("No HRTFs found\n");
    else
    {
        ALCint attr[5];
        ALCint index = -1;
        ALCint i;

        printf("Available HRTFs:\n");
        for(i = 0; i < num_hrtf; i++)
        {
            const ALCchar *name = alcGetStringiSOFT(self->device, ALC_HRTF_SPECIFIER_SOFT, i);
            printf("    %d: %s\n", i, name);

            if(hrtfname && strcmp(name, hrtfname) == 0) index = i;
        }

        i = 0;
        attr[i++] = ALC_HRTF_SOFT;
        attr[i++] = ALC_TRUE;
        if(index == -1)
        {
            if(hrtfname) printf("HRTF \"%s\" not found\n", hrtfname);
            printf("Using default HRTF...\n");
        }
        else
        {
            printf("Selecting HRTF %d...\n", index);
            attr[i++] = ALC_HRTF_ID_SOFT;
            attr[i++] = index;
        }
        attr[i] = 0;

        if(!alcResetDeviceSOFT(self->device, attr))
            printf("Failed to reset device: %s\n", alcGetString(self->device, alcGetError(self->device)));
	}
	alcGetIntegerv(self->device, ALC_HRTF_SOFT, 1, &hrtf_state);
	if(!hrtf_state) printf("HRTF not enabled!\n");
	else
	{
		const ALchar *name = alcGetString(self->device, ALC_HRTF_SPECIFIER_SOFT);
		printf("HRTF enabled, using %s\n", name);
	}
#endif

#endif
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

	vec3_t pos = c_node_pos_to_global(nc, Z3);
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

	ct_listener(ct, WORLD, 0, sig("world_update"), c_openal_update);
}

