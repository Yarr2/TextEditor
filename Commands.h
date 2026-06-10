#pragma once


void help();
void append_text(struct text* text, struct stack* stack);
void start_new_line(struct text* text);
void save_text_to_file(struct text* text);
void load_from_file(struct text* text);
void insert_into_text(struct text* text, struct stack* stack);
void search_substring(struct text* text);
void delete_from_text(struct text* text, struct stack* stack);
void undo_commands(struct text* text, struct stack* stack, struct stack* redo_stack);
void redo_commands(struct text* text, struct stacl* redo_stack);
void cut_symbols(struct text* text, struct string* copy_buffer, struct stack* stack);
void paste_symbols(struct text* text, struct string* copy_buffer, struct stack* stack);
void copy_symbols(struct text* text, struct string* copy_buffer);
void insert_with_replacement(struct text* text, struct stack* stack);