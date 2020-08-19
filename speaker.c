#include "speaker.h"
#include "openal.h"
#include "../candle/components/node.h"
#include "../candle/components/model.h"
#include "../candle/utils/drawable.h"
#include "../candle/components/sprite.h"
#include "../candle/components/node.h"
#include "../candle/systems/editmode.h"
#include "../candle/systems/sauces.h"

#include <stdio.h>
#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>

static int32_t c_speaker_update_position(c_speaker_t *self);

static mat_t *g_speaker_mat;

void c_speaker_init(c_speaker_t *self)
{
	alGenSources((ALuint)1, &self->source);

	alSourcei(self->source, AL_SOURCE_RELATIVE, AL_FALSE);
	/* alSourcef(self->source, AL_ROLLOFF_FACTOR, 1); */
	/* alSourcef(self->source, AL_REFERENCE_DISTANCE, 6); */
	/* alSourcef(self->source, AL_MAX_DISTANCE, 15); */

	alerr();

	if(!g_speaker_mat)
	{
		g_speaker_mat = mat_new("speaker", "default");
		mat1t(g_speaker_mat, ref("albedo.texture"), sauces("speaker"));
		mat1f(g_speaker_mat, ref("albedo.blend"), 1.0f);
		mat4f(g_speaker_mat, ref("emissive.color"), vec4(0.4, 0.6, 0.8, 1.0f));
	}

	drawable_init(&self->draw, ref("widget"));
	drawable_add_group(&self->draw, ref("selectable"));
	drawable_set_vs(&self->draw, sprite_vs());
	drawable_set_mat(&self->draw, g_speaker_mat);
	drawable_set_entity(&self->draw, c_entity(self));
	drawable_set_xray(&self->draw, true);
	drawable_set_mesh(&self->draw, sprite_mesh());

	c_speaker_update_position(self);
}

void c_speaker_set_gain(c_speaker_t *self, float gain)
{
	alSourcef(self->source, AL_GAIN, gain);
	alerr();
}

void c_speaker_set_pitch(c_speaker_t *self, float pitch)
{
	alSourcef(self->source, AL_PITCH, 1);
	alerr();
}

/* static int c_speaker_update(c_speaker_t *self) */
/* { */
/* 	if (self->playing) */
/* 	{ */
/* 		float val = sound_get_value(self->playing, c_speaker_get_byte_offset(self)); */
/* 		c_spatial_t *sp = c_spatial(self); */
/* 		c_spatial_lock(sp); */
/* 		c_spatial_set_pos(sp, vec3(0, pow(val, 2) * 2.0, 0)); */
/* 		c_spatial_set_rot(sp, 0, 0, 1, pow(val, 3.0)); */
/* 		c_spatial_scale(sp, vec3(1, 1.0 - sin(val * 10.0) * 0.004, 1.0)); */
/* 		c_spatial_unlock(sp); */
/* 	} */
/* } */

static bool_t c_speaker_playing(c_speaker_t *self)
{
	if (self->playing)
	{
		ALenum state;
		alGetSourcei(self->source, AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING)
		{
			self->playing = NULL;
			c_openal(&SYS)->rel_sound_playing--;
		}
		else
		{
			return true;
		}
	}
	return false;
}

static int32_t c_speaker_update_position(c_speaker_t *self)
{
	c_node_t *nc = c_node(self);
	vec3_t p;

	drawable_set_transform(&self->draw, nc->model);

	if (!c_speaker_playing(self))
	{
		return CONTINUE;
	}

	c_node_update_model(nc);
	p = c_node_pos_to_global(nc, vec3(0, 0, 0));

	alSource3f(self->source, AL_POSITION, p.x, p.y, p.z); alerr();
	alSource3f(self->source, AL_VELOCITY, 0, 0, 0); alerr();
	/* alSource3f(source, AL_VELOCITY, 0, 0, 0); */
	/* alerr(); */

	/* mat4_t model = node->model; */
	/* if(self->scale_dist > 0.0f) */
	/* { */
	/* 	vec3_t pos = mat4_mul_vec4(model, vec4(0,0,0,1)).xyz; */
	/* 	float dist = vec3_dist(pos, c_renderer(&SYS)->bound_camera_pos); */
	/* 	mat4_t model = mat4_scale_aniso(model, vec3(dist * self->scale_dist)); */
	/* } */

	return CONTINUE;
}

void c_speaker_pause(c_speaker_t *self)
{

}

void c_speaker_stop(c_speaker_t *self)
{

}

int32_t c_speaker_get_byte_offset(c_speaker_t *self)
{
	int32_t offset = 0;
	if (self->playing)
	{
		alGetSourcei(self->source, AL_BYTE_OFFSET, &offset);
	}
	return offset;
}

void c_speaker_play(c_speaker_t *self, sound_t *sound, bool_t loop)
{
	if(!sound) return;
	ALCenum error;

	alSourceStop(self->source);
	error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);

	alSourcei(self->source, AL_LOOPING, loop);
	alerr();

	alSourcei(self->source, AL_BUFFER, sound->buffer);
	alerr();
	/* switch(error) */
	/* { */
	/* 	case AL_INVALID_NAME: */
	/* 		printf("invalid name\n"); */
	/* 		break; */
	/* 	case AL_INVALID_ENUM: */
	/* 		printf("invalid enum\n"); */
	/* 		break; */
	/* 	case AL_INVALID_VALUE: */
	/* 		printf("invalid value\n"); */
	/* 		break; */
	/* 	case AL_INVALID_OPERATION: */
	/* 		printf("invalid operation\n"); */
	/* 		break; */
	/* 	case AL_OUT_OF_MEMORY: */
	/* 		printf("out of mem\n"); */
	/* 		break; */

	/* } */

	c_openal(&SYS)->rel_sound_playing++;

	c_speaker_update_position(self);

	alSourcePlay(self->source);
	alerr();

	self->playing = sound;
}

c_speaker_t *c_speaker_new()
{
	c_speaker_t *self = component_new(ct_speaker);

	return self;
}

void c_speaker_destroy(c_speaker_t *self)
{
	drawable_set_mesh(&self->draw, NULL);
	alDeleteSources(1, &self->source);
}

void ct_speaker(ct_t *self)
{
	ct_init(self, "speaker", sizeof(c_speaker_t));
	ct_set_init(self, (init_cb)c_speaker_init);
	ct_set_destroy(self, (destroy_cb)c_speaker_destroy);
	ct_add_dependency(self, ct_node);
	ct_add_listener(self, ENTITY, 0, sig("node_changed"), c_speaker_update_position);
}

