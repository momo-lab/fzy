#include <stdlib.h>
#include <search.h>

#include "multi_select.h"

static int compare(const void *pa, const void *pb) {
	if (*(size_t *)pa < *(size_t *)pb) {
		return -1;
	} else if (*(size_t *)pa > *(size_t *)pb) {
		return 1;
	} else {
		return 0;
	}
}

void multi_select_init(multi_select_t *m) {
	m->indexes = NULL;
	m->size = 0;
}

void multi_select_destroy(multi_select_t *m) {
	tdestroy((void *)m->indexes, free);
	m->indexes = NULL;
	m->size = 0;
}

int multi_select_get(multi_select_t *m, size_t index) {
	size_t *result = tfind((void *)&index, &m->indexes, compare);
	return (result != NULL);
}

void append_index(multi_select_t *m, size_t index) {
	size_t *node = (size_t *)malloc(sizeof(size_t));
	if (node == NULL) {
		fprintf(stderr, "Error: Can't allocate memory\n");
		abort();
	}
	*node = index;
	void *ret = tsearch((void *)node, &(m->indexes), compare);
	if (ret == NULL) {
		fprintf(stderr, "Error: Can't allocate memory\n");
		abort();
	}
}

void remove_index(multi_select_t *m, size_t index) {
	tdelete((void *)&index, &m->indexes, compare);
}

void multi_select_toggle(multi_select_t *m, size_t index) {
	if (multi_select_get(m, index)) {
		remove_index(m, index);
		m->size--;
	} else {
		append_index(m, index);
		m->size++;
	}
}

size_t multi_select_size(multi_select_t *m) {
	return m->size;
}

static size_t *twalk_result = NULL;
static size_t twalk_reslt_size = 0;
static void twalk_action(const void *nodep, const VISIT which, const int depth) {
	(void)depth; // unused parameter
	size_t *indexp;
	switch (which) {
		case preorder:
			break;
		case postorder:
			indexp = *(size_t **)nodep;
			twalk_result[twalk_reslt_size++] = *indexp;
			break;
		case endorder:
			break;
		case leaf:
			indexp = *(size_t **)nodep;
			twalk_result[twalk_reslt_size++] = *indexp;
			break;
	}
}

size_t *multi_select_indexes(multi_select_t *m) {
	twalk_result = (size_t *)malloc(m->size * sizeof(size_t));
	if (!twalk_result) {
		fprintf(stderr, "Error: Can't allocate memory\n");
		abort();
	}
	twalk_reslt_size = 0;
	twalk(m->indexes, twalk_action);
	return twalk_result;
}
