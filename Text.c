#include <stdio.h>
#include <stdlib.h>
#include "String.c"

struct line {
	struct string* value;
	struct line* pointer;
};

struct text {
	struct line* start;
	struct line* finish;
};

void create_text(struct text* text) {
	struct line* start = (struct line*)malloc(sizeof(struct line));
	start->pointer = NULL;
	struct string* string = (struct string*)malloc(sizeof(struct string));
	create_string(string);
	start->value = string;
	text->finish = start;
	text->start = start;
}
void add_line(struct text* text) {
	struct line* new_line = (struct line*)malloc(sizeof(struct line));
	new_line->pointer = NULL;

	struct string* string = (struct string*)malloc(sizeof(struct string));
	create_string(string);
	new_line->value = string;

	text->finish->pointer = new_line;
	text->finish = new_line;
}
void print_text(struct text* text) {
	struct line* line = text->start;
	while (line->pointer != NULL) {
		print_string(line->value);
		printf("\n");
		line = line->pointer;
	}
	print_string(line->value);
	printf("\n");

}
void insert_text(struct text* text, int line, int index, struct string* string) {
	struct line* node = text->start;
	int counter = 0;
	while (counter < line && node->pointer != NULL) {
		counter++;
		node = node->pointer;
	}
	if (counter == line) {
		insert_text_string(node->value, index, string);
		return;
	}
	else {
		printf("There is no line with index %d\n", line);
		return;
	}
}
void destroy_text(struct text* text) {
	destroy_string(text->start->value);
	destroy_string(text->finish->value);
	free(text->start->pointer);
	free(text->finish->pointer);
	free(text);
}