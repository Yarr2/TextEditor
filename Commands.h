#pragma once


void help();
void append_text(struct text* text);
void start_new_line(struct text* text);
void save_text_to_file(struct text* text);
void load_from_file(struct text* text);
void insert_into_text(struct text* text);
void search_substring(struct text* text);
void delete_from_text(struct text* text);
void undo_commands(struct text* text);
void redo_commands(struct text* text);
void cut_symbols(struct text* text, struct string* copy_buffer);
void paste_symbols(struct text* text, struct string* copy_buffer);
void copy_symbols(struct text* text, struct string* copy_buffer);
void insert_with_replacement(struct text* text);