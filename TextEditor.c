#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Text.h"
#include "String.h"
#include "Commands.h"
#include "Stack.h"

void get_command(char (*character)[2]) {
	
	scanf_s("%c", character, 2);

	char temp_char = character[0];
	
	while (temp_char != '\n') {
		scanf_s("%c", &temp_char, 1);
	}

}

void process_command(int command,struct text* text,struct string* copy_buffer, struct stack* stack, struct stack* redo_stack) {
	if (command == 1 || command ==  2 || command == 6 ||  command == 8 ||
		command == 11 || command == 12 || command == 14) {
		clear_stack(redo_stack);
	}
	switch (command) { // functions from Command.c
	case 0:
	{
		help();
		break;
	}
	case 1:
	{
		append_text(text, stack);// stack
		break;
	}
	case 2:
	{
		start_new_line(text);
		break;
	}
	case 3:
	{
		save_text_to_file(text);
		break;
	}
	case 4:
	{
		load_from_file(text);
		break;
	}
	case 5:
	{
		print_text(text);
		break;
	}
	case 6:
	{
		insert_into_text(text, stack); // stack
		break;
	}
	case 7:
	{
		search_substring(text);
		break;
	}
	case 8: 
	{
		delete_from_text(text, stack); // stack
		break;
	}
	case 9:
	{
		undo_commands(text, stack, redo_stack);
		break;
	}
	case 10:
	{
		redo_commands(text, stack, redo_stack);
		break;
	}
	case 11:
	{
		cut_symbols(text, copy_buffer ,stack); // stack
		break;
	}
	case 12:
	{
		paste_symbols(text, copy_buffer, stack); // stack
		break;
	}
	case 13:
	{
		copy_symbols(text, copy_buffer);
		break;
	}
	case 14:
	{
		insert_with_replacement(text, stack); // stack
		break;
	}
	case 15:
	{
		printf("Cursor logic to be implemented\n");
		break;
	}
	case 16: 
	{
		struct data* data = (struct data*)malloc(sizeof(struct data));

		peek(stack,data);
		printf("Last command - ");
		switch (data->command) {
		case Delete: printf("DELETE"); break;
		case Insert: printf("INSERT"); break;
		case InsertWithReplacment: printf("REPLACEMENT"); break;
		default: printf("UNKNOWN"); break;
		}

		printf(",index - %d, number - %d\n", data->index, data->number_of_symbols);
		free(data);
	}
	}
}

int main() {
	int debug = 0;
	struct string* copy_buffer = (struct string*)malloc(sizeof(struct string));
	create_string(copy_buffer);
	struct text* text = (struct text*)malloc(sizeof(struct text));
	create_text(text);
	struct stack* stack = create_stack();
	struct stack* redo_stack = create_stack();
	if (debug) {
		printf("DEBUG MODE\n");
		destroy_text(text);
		return 0;
	}
	
	printf("Welcome to our text editor\n");
	
	while (1) {

		printf("Enter command you want to execute(0 for help) > ");
		int command = -1;
		scanf_s("%d", &command);
		char character;
		scanf_s("%c", &character, 1);
		if (character == 'P') {
			printf("Program exited\n");
			destroy_string(copy_buffer);
			destroy_text(text);
			destroy_stack(stack);
			destroy_stack(redo_stack);
			return 0;
		}
		while (character != '\n')
		{
			scanf_s("%c", &character, 1);
		}

		process_command(command,text,copy_buffer, stack, redo_stack);
	}
	return 0;
}