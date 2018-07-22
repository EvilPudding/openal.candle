#include "openal.h"
#include "sound.h"

#include <systems/sauces.h>
#include <components/camera.h>
#include <components/node.h>

#include <stdio.h>
#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <AL/alext.h>


static LPALCGETSTRINGISOFT alcGetStringiSOFT;
static LPALCRESETDEVICESOFT alcResetDeviceSOFT;

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

	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

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

	sauces_loader(ref("wav"), sound_loader);
}

int c_openal_update(c_openal_t *self)
{
	ct_t *cameras = ecm_get(ref("camera"));
	c_camera_t *camera = (c_camera_t*)ct_get_nth(cameras, 0);
	if(!camera) return CONTINUE;
	c_node_t *nc = c_node(camera);
	c_node_update_model(nc);

	vec3_t pos = mat4_mul_vec4(nc->model, vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	vec3_t at = vec3_norm(mat4_mul_vec4(nc->model,
				vec4(0.0f, 0.0f, -1.0f, 0.0f)).xyz);
	vec3_t up = vec3_norm(mat4_mul_vec4(nc->model,
				vec4(0.0f, 1.0f, 0.0f, 0.0f)).xyz);

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

