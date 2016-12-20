#ifndef OPTIONS_H
#define OPTIONS_H OPTIONS_H

typedef struct {
	int benchmark;
	const char *filter;
	const char *init_search;
	const char *tty_filename;
	int show_scores;
	int show_count;
	unsigned int num_lines;
	unsigned int scrolloff;
	const char *prompt;
	int select_1;
} options_t;

void options_parse(options_t *options, int argc, char *argv[]);

#endif
