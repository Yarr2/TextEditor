#pragma once
struct line {
	struct string* value;
	struct line* pointer;
};

struct text {
	struct line* start;
	struct line* finish;
};
void create_text(struct text* text);
void add_line(struct text* text);
void print_text(struct text* text);
void insert_text(struct text* text, int line, int index, struct string* string);
void destroy_text(struct text* text);
void load_text(struct text* text, char* path);
void save_text(struct text* text, char* path);
void search_in_text(struct text* text, struct string* string);
void clear(struct text* text);