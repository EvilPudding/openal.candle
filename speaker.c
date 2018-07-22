#include "speaker.h"
#include "openal.h"
#include <components/node.h>
#include <components/model.h>
#include <components/mesh_gl.h>
#include <components/sprite.h>
#include <components/node.h>

#include <stdio.h>
#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

/* #include "build/speaker.png.sauce.c" */
extern unsigned char speaker_png[];
extern unsigned int speaker_png_len;

entity_t g_speaker = entity_null;

static int c_speaker_update_position(c_speaker_t *self);

void c_speaker_init(c_speaker_t *self)
{
	alGenSources((ALuint)1, &self->source);

	alSourcei(self->source, AL_SOURCE_RELATIVE, AL_FALSE);
	/* alSourcef(self->source, AL_ROLLOFF_FACTOR, 1); */
	/* alSourcef(self->source, AL_REFERENCE_DISTANCE, 6); */
	/* alSourcef(self->source, AL_MAX_DISTANCE, 15); */

	ALCenum error = alGetError(); if (error != AL_NO_ERROR) printf("error at %d\n", __LINE__);
	c_speaker_update_position(self);

	if(!g_speaker)
	{
		mat_t *m = mat_new("speaker");
		m->albedo.texture = texture_from_memory(speaker_png, speaker_png_len);
		m->albedo.texture_blend = 1.0f;
		m->albedo.texture_scale = 1.0f;
		mesh_t *mesh = mesh_new();
		mesh_quad(mesh);
		g_speaker = entity_new(c_node_new(), c_model_new(mesh, m, 0, 0));
		c_node(&g_speaker)->ghost = 1;
	}
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

static int c_speaker_render_visible(c_speaker_t *self)
{
	shader_t *shader = vs_bind(sprite_vs());
	if(!shader) return STOP;
	c_node_t *node = c_node(self);
	if(node)
	{
		c_node_update_model(node);
#ifdef MESH4
		shader_update(shader, &node->model, node->angle4);
#else
		shader_update(shader, &node->model);
#endif
	}
	glDepthRange(0, 0.01);
	c_mesh_gl_draw(c_mesh_gl(&g_speaker), 0);
	glDepthRange(0.0, 1.00);
	return CONTINUE;
}

REG()
{
	ct_t *ct = ct_new("speaker", sizeof(c_speaker_t), c_speaker_init,
			c_speaker_destroy, 1, ref("node"));
	ct_listener(ct, ENTITY, sig("spacial_changed"), c_speaker_update_position);
	ct_listener(ct, WORLD, sig("render_visible"), c_speaker_render_visible);
}

