#include <stdio.h>
#include <stdlib.h>

#include "AT.h"

extern AT_COMMAND_DATA at_command_data;
extern AT_ERROR at_error;

void validate_number_of_args(int provided_args_number, int correct_args_number){
	if(provided_args_number != correct_args_number){
		printf("Error! Invalid number of arguments!\n");
		printf("Try: ./filename <arg1>\n");
		exit(EXIT_FAILURE);
	}
}

void parse_file(char *filename){
	FILE *fp;
	char character;
	uint8_t state;

	fp = fopen(filename, "rb");
	if(fp != NULL){
		do{
			character = (char)fgetc(fp);
			if(character != EOF){
				state = at_command_parse(character);
			}
			
			if(state == 2){
				printf("%s\n", at_error.error_message);
			}

		}while(character != EOF);

		printf("\n");

		for (int i = 0; i <= at_command_data.line_count - 1; i++){
			int j = 0;
			do{
					printf("%c", at_command_data.data[i][j++]);
			}while(at_command_data.data[i][j] != '\n');

			printf("\n");
		}
		
	}
	else{
		printf("Error at file opening.\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
}

int main(int argc, char *argv[])
{
	validate_number_of_args(argc, 2);
	parse_file(argv[1]);
	
	return 0;
}