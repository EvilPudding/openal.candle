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

void ct_openal(ct_t *self);
DEF_CASTER(ct_openal, c_openal, c_openal_t)

c_openal_t *c_openal_new(void);
void c_openal_set_listener(c_openal_t *self, entity_t listener);

#define alerr() _check_al_error(__FILE__,__LINE__)
void _check_al_error(const char *file, int line);

#endif /* !OPENAL_H */
