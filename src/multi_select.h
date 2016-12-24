#ifndef MULTI_SELECT_H
#define MULTI_SELECT_H MULTI_SELECT_H

#include <stdio.h>

typedef struct {
	void *indexes;
	size_t size;
} multi_select_t;

void multi_select_init(multi_select_t *m);
void multi_select_destroy(multi_select_t *m);
int multi_select_get(multi_select_t *m, size_t index);
void multi_select_toggle(multi_select_t *m, size_t index);
size_t multi_select_size(multi_select_t *m);
size_t *multi_select_indexes(multi_select_t *m);

#endif
