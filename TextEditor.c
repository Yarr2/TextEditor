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

void process_command(int command,struct text* text,struct string* copy_buffer) {
	switch (command) { // functions from Command.c
	case 0:
	{
		help();
		break;
	}
	case 1:
	{
		append_text(text);
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
		insert_into_text(text);
		break;
	}
	case 7:
	{
		search_substring(text);
		break;
	}
	case 8: 
	{
		delete_from_text(text);
		break;
	}
	case 9:
	{
		undo_commands(text);
		break;
	}
	case 10:
	{
		redo_commands(text);
		break;
	}
	case 11:
	{
		cut_symbols(text, copy_buffer);
		break;
	}
	case 12:
	{
		paste_symbols(text, copy_buffer);
		break;
	}
	case 13:
	{
		copy_symbols(text, copy_buffer);
		break;
	}
	case 14:
	{
		insert_with_replacement(text);
		break;
	}
	case 15:
	{
		printf("Cursor logic to be implemented\n");
		break;
	}
	}
}

int main() {
	int debug = 0;
	struct string* copy_buffer = (struct string*)malloc(sizeof(struct string));
	create_string(copy_buffer);
	struct text* text = (struct text*)malloc(sizeof(struct text));
	create_text(text);

	if (debug) {
		printf("DEBUG MODE\n");
		struct stack* stack = create_stack();
		struct data* data = (struct data*)malloc(sizeof(struct data));
		data->value = 15;
		push(stack, data);
		push(stack, data);
		push(stack, data);

		data->value = 67;
		push(stack, data);
		data->value = 0;
		pop(stack,data);
		print_stack(stack);
		
		printf("Popped - %d", data->value);
		destroy_stack(stack);
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
			destroy_text(text);
			return 0;
		}
		while (character != '\n')
		{
			scanf_s("%c", &character, 1);
		}

		process_command(command,text,copy_buffer);
	}
	destroy_text(text);
	return 0;
}