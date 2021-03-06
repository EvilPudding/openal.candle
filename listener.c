#include "listener.h"
#include "openal.h"
#include "../candle/components/node.h"
#include "../candle/components/model.h"
#include "../candle/utils/drawable.h"
#include "../candle/components/sprite.h"
#include "../candle/components/node.h"
#include "../candle/systems/editmode.h"

#include <stdio.h>
#include <stdlib.h>
#include "alw.h"

static int32_t c_listener_update_position(c_listener_t *self);

void c_listener_init(c_listener_t *self)
{
	c_listener_update_position(self);
}

static int32_t c_listener_update_position(c_listener_t *self)
{
	c_node_t *nc;
	vec3_t pos, at, up;
	ALfloat listenerOri[6];

	if (!c_openal(&SYS)->rel_sound_playing)
	{
		return CONTINUE;
	}

	nc = c_node(self);

	pos = c_node_pos_to_global(nc, Z3);
	at = c_node_dir_to_global(nc, vec3(0.0f, 0.0f, -1.0f));
	up = c_node_dir_to_global(nc, vec3(0.0f, 1.0f, 0.0f));

	listenerOri[0] = at.x;
	listenerOri[1] = at.y;
	listenerOri[2] = at.z;
	listenerOri[3] = up.x;
	listenerOri[4] = up.y;
	listenerOri[5] = up.z;

	alwListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	alwListenerfv(AL_ORIENTATION, listenerOri);
	alwListener3f(AL_VELOCITY, 0, 0, 0);

	alerr();

	return CONTINUE;
}

c_listener_t *c_listener_new()
{
	c_listener_t *self = component_new(ct_listener);

	return self;
}

void ct_listener(ct_t *self)
{
	ct_init(self, "listener", sizeof(c_listener_t));
	ct_set_init(self, (init_cb)c_listener_init);
	ct_add_dependency(self, ct_node);
	ct_add_listener(self, ENTITY, 0, sig("node_changed"), c_listener_update_position);
}

