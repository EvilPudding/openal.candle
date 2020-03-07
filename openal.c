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

void _check_al_error(const char *file, int line)
{
	ALCenum err;
	int got_error = 0;
	char message[512];
	static int count = 0;
	static char last_error[512] = "";

	err = alGetError();
	while (err != AL_NO_ERROR) {
		char *error = NULL;
		switch(err)
		{
			case AL_INVALID_OPERATION: error="AL_INVALID_OPERATION"; break;
			case AL_INVALID_NAME: error="AL_INVALID_NAME"; break;
			case AL_INVALID_ENUM: error="AL_INVALID_ENUM"; break;
			case AL_INVALID_VALUE: error="AL_INVALID_VALUE"; break;
			case AL_OUT_OF_MEMORY: error = "AL_OUT_OF_MEMORY"; break;
		}
		snprintf(message, sizeof(message), "GL_%s - %s:%d", error, file, line);
		if(!strncmp(last_error, message, sizeof(last_error)))
		{
			printf("\b\b\r%s%6d\n", message, ++count);
		}
		else
		{
			count = 0;
			printf("%s\n", message);
			strncpy(last_error, message, sizeof(last_error));
		}
		err = alGetError();
		got_error = 1;
	}
	if(got_error)
	{
		__builtin_trap();
		exit(1);
	}
}

void c_openal_init(c_openal_t *self)
{
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

c_openal_t *c_openal_new()
{
	c_openal_t *self = component_new(ct_openal);

	return self;
}

void c_openal_destroy(c_openal_t *self)
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(self->context);
	alcCloseDevice(self->device);
}

void ct_openal(ct_t *self)
{
	ct_init(self, "openal", sizeof(c_openal_t));
	ct_set_init(self, (init_cb)c_openal_init);
	ct_set_destroy(self, (destroy_cb)c_openal_destroy);
}

