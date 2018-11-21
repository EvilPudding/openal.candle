#include "speaker.h"
#include "openal.h"
#include <components/node.h>
#include <components/model.h>
#include <utils/drawable.h>
#include <components/sprite.h>
#include <components/node.h>
#include <systems/editmode.h>

#include <stdio.h>
#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

/* #include "build/speaker.png.sauce.c" */
extern unsigned char speaker_png[];
extern unsigned int speaker_png_len;

static int c_speaker_update_position(c_speaker_t *self);
static int c_speaker_editmode_toggle(c_speaker_t *self);

static mat_t *g_speaker_mat;

void c_speaker_init(c_speaker_t *self)
{
	alGenSources((ALuint)1, &self->source);

	alSourcei(self->source, AL_SOURCE_RELATIVE, AL_FALSE);
	/* alSourcef(self->source, AL_ROLLOFF_FACTOR, 1); */
	/* alSourcef(self->source, AL_REFERENCE_DISTANCE, 6); */
	/* alSourcef(self->source, AL_MAX_DISTANCE, 15); */

	ALCenum error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);

	if(!g_speaker_mat)
	{
		g_speaker_mat = mat_new("speaker");
		g_speaker_mat->albedo.texture = texture_from_memory(speaker_png, speaker_png_len);
		g_speaker_mat->albedo.blend = 1.0f;
		g_speaker_mat->emissive.color = vec4(0.4, 0.6, 0.8, 1.0f);
	}

	drawable_init(&self->draw, ref("transparent"), NULL);
	drawable_add_group(&self->draw, ref("selectable"));
	drawable_set_vs(&self->draw, sprite_vs());
	drawable_set_mat(&self->draw, g_speaker_mat->id);
	drawable_set_entity(&self->draw, c_entity(self));
	drawable_set_xray(&self->draw, 1);

	c_speaker_editmode_toggle(self);

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
	alSource3f(self->source, AL_VELOCITY, 0, 0, 0);
	ALCenum error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
	/* alSource3f(source, AL_VELOCITY, 0, 0, 0); */
	/* error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__); */

	/* mat4_t model = node->model; */
	/* if(self->scale_dist > 0.0f) */
	/* { */
	/* 	vec3_t pos = mat4_mul_vec4(model, vec4(0,0,0,1)).xyz; */
	/* 	float dist = vec3_dist(pos, c_renderer(&SYS)->bound_camera_pos); */
	/* 	mat4_t model = mat4_scale_aniso(model, vec3(dist * self->scale_dist)); */
	/* } */
	drawable_set_transform(&self->draw, nc->model);

	return CONTINUE;
}

void c_speaker_pause(c_speaker_t *self)
{

}

void c_speaker_stop(c_speaker_t *self)
{

}

void c_speaker_play(c_speaker_t *self, sound_t *sound, int loop)
{
	if(!sound) return;
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
	drawable_set_mesh(&self->draw, NULL);
	alDeleteSources(1, &self->source);
}

static int c_speaker_editmode_toggle(c_speaker_t *self)
{
	c_editmode_t *edit = c_editmode(&SYS);
	if(!edit) return CONTINUE;

	if(edit->control)
	{
		drawable_set_mesh(&self->draw, sprite_mesh());
	}
	else
	{
		drawable_set_mesh(&self->draw, NULL);
	}
	return CONTINUE;
}

REG()
{
	ct_t *ct = ct_new("speaker", sizeof(c_speaker_t), c_speaker_init,
			c_speaker_destroy, 1, ref("node"));
	ct_listener(ct, WORLD, sig("editmode_toggle"), c_speaker_editmode_toggle);
	ct_listener(ct, ENTITY, sig("node_changed"), c_speaker_update_position);
}

