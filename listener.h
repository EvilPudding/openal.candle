#ifndef LISTENER_H
#define LISTENER_H

#include <ecs/ecm.h>

typedef struct c_listener_t
{
	c_t super;
} c_listener_t;

void ct_listener(ct_t *self);
DEF_CASTER(ct_listener, c_listener, c_listener_t)

c_listener_t *c_listener_new(void);

#endif /* !LISTENER_H */
