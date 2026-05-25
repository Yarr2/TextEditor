#include <stdio.h>
#include <stdlib.h>
void get_first_char(char* character) {
	
	scanf("%c", character);
	
	char temp_char = character[0];
	
	while (temp_char != '\n') {
		scanf("%c", &temp_char);
	}

}
int main() {
	int debug = 0;

	if (debug) {
		// something I want to test
		return 0;
	}
	
	printf("Welcome to our text editor\n");
	
	while (1) {

		printf("Enter command you want to execute > ");
		char word;
		get_first_char(&word);
		printf("Your command is %c\n", word);
		if (word == '\n') {
			return 0;
		}
	}
	return 0;
}