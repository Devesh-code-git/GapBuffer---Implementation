#include <stdio.h>
#include <stdlib.h>

typedef struct GapBuffer {
	char *buffer;
	int cursor;
	int buffer_size;
	int gap_end;
	int gap_size;
} GapBuffer;

void resize(GapBuffer *g, char c);

GapBuffer* create(size_t size) {
	GapBuffer *data = malloc(sizeof(GapBuffer));
	if (!data) {
		return NULL;
	}
	
	data->buffer = calloc(size, sizeof(char));
	if (!(data->buffer)) {
		free(data);
		return NULL;
	}
	
	data->cursor = 0;
	data->buffer_size = (int)size;
	data->gap_end = (int)size - 1;
	data->gap_size = (data->gap_end) - (data->cursor);
	
	return data;
}

void show(GapBuffer *g) {
	int size = g->buffer_size;
	
	for (int i = 0; i < size; i++) {
		if (g->buffer[i] == '\0') {
			printf("_");
		}
		else {
			printf("%c", g->buffer[i]);
		}
	}
}

void insert(GapBuffer *g, char c) {
	if (g == NULL) {
		return;
	}
	else if (g->gap_size <= 0) {
		resize(g, c);
	}
	else {
		g->buffer[g->cursor] = c;
		g->cursor++;
		g->gap_size = (g->gap_end) - (g->cursor);
	}
}

void backspace(GapBuffer *g) {
	if (g == NULL || g->cursor <= 0) {
		return;
	}
	
	g->cursor--;
	g->buffer[g->cursor] = '\0';
	g->gap_size = (g->gap_end) - (g->cursor);
}

void left(GapBuffer *g) {
	if (g == NULL || g->cursor <= 0) {
		return;
	}
	
	char c = g->buffer[(g->cursor) - 1];
	
	g->cursor--;
	g->gap_end--;
	g->gap_size = (g->gap_end) - (g->cursor);
	
	g->buffer[g->cursor] = '\0';
	g->buffer[(g->gap_end) + 1] = c;
}

void right(GapBuffer *g) {
	if (g == NULL || g->gap_end >= (g->buffer_size) - 1) {
		return;
	}
	
	char c = g->buffer[g->gap_end + 1];
	
	g->cursor++;
	g->gap_end++;
	g->gap_size = (g->gap_end) - (g->cursor);
	
	g->buffer[g->gap_end] = '\0';
	g->buffer[(g->cursor) - 1] = c;
}

void resize(GapBuffer *g, char c) {
	char* new_arr = calloc((size_t)((g->buffer_size) * 2), sizeof(char));
	if (!(new_arr)) {
		return;
	}
	
	for (int i = 0; i < g->buffer_size; i++) {
		new_arr[i] = g->buffer[i];
	}
	
	new_arr[g->cursor] = c;
	int l = (g->buffer_size) - 1 - (g->cursor);
	g->cursor = g->buffer_size;
	
	free(g->buffer);
	g->buffer = new_arr;
	
	g->gap_end = ((g->buffer_size)*2) - 1;
	g->buffer_size = (g->buffer_size)*2;
	
	g->gap_size = (g->gap_end) - (g->cursor);
	
	for (int i = 0; i < l; i++) {
		left(g);
	}
}

void delete(GapBuffer *g) {
	free(g->buffer);
	free(g);
}
