#ifndef OPENAL_H
#define OPENAL_H

#include <ecs/ecm.h>

typedef struct c_openal_t
{
	c_t super;
	void *device;
	void *context;
	entity_t listener;
} c_openal_t;

DEF_CASTER("openal", c_openal, c_openal_t)

c_openal_t *c_openal_new(void);
void c_openal_set_listener(c_openal_t *self, entity_t listener);

#endif /* !OPENAL_H */
