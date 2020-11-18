#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AT.h"

AT_COMMAND_DATA at_command_data;
AT_ERROR at_error;

STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t current_character){
	
	static uint32_t state = 0;
	static int string_size = 0;

	switch(state){
		
		case 0:{
			if (current_character == 0x0D){
				state = 1;
			}
			break;
		}

		case 1:{
			if (current_character == 0x0A){
				state = 2;
			}
			else{
				at_error.state_number = 1;
				strcpy(at_error.error_message, "Error at state 1");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 2: {
			switch (current_character){
				case '+': {
					state = 3;
					break;
				}

				case 'O': {
					state = 4;
					break;
				}

				case 'E': {
					state = 5;
					break;
				}

				default: {
					state = 6;
				}
			}
			break;
		}

		case 3: {
			if (current_character != 0x0D){
				state = 30;
				at_command_data.data[at_command_data.line_count][string_size++] = current_character;
			}
			else{
				at_error.state_number = 3;
				strcpy(at_error.error_message, "Error at state 3");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 30:{
			if (current_character != 0x0D){
				state = 30;
				if(string_size < AT_COMMAND_MAX_LINE_SIZE)
					at_command_data.data[at_command_data.line_count][string_size++] = current_character;

			}
			else{
				state = 31;
			}
			break;
		}

		case 31: {
			if (current_character == 0x0A){
				state = 32;
				at_command_data.data[at_command_data.line_count][string_size] = 0x0A;
				string_size = 0;
				at_command_data.line_count++;
			}
			else{
				at_error.state_number = 31;
				strcpy(at_error.error_message, "Error at state 31");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 32: {
			if (current_character == '+'){
				state = 3;
			}
			else if (current_character == 0x0D){
				state = 33;
			}
			else {
				at_error.state_number = 32;
				strcpy(at_error.error_message, "Error at state 32");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 33: {
			if (current_character == 0x0A){
				state = 34;
			}
			else{
				at_error.state_number = 33;
				strcpy(at_error.error_message, "Error at state 33");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 34: {
			if (current_character == 'O'){
				state = 4;
				at_command_data.data[at_command_data.line_count][string_size++] = 'O';
			}
			else if (current_character == 'E'){
				state = 5;
				at_command_data.data[at_command_data.line_count][string_size++] = 'E';
			}
			else{
				at_error.state_number = 34;
				strcpy(at_error.error_message, "Error at state 34");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
		}

		case 4:{
			printf("%c\n", current_character);
			if (current_character == 'K'){
				state = 40;
				at_command_data.data[at_command_data.line_count][string_size++] = 'K';
			}
			else{
				at_error.state_number = 4;
				strcpy(at_error.error_message, "Error at state 4");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 40:{
			if (current_character == 0x0D){
				state = 41;
			}
			else{
				at_error.state_number = 40;
				strcpy(at_error.error_message, "Error at state 40");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 41: {
			if (current_character == 0x0A){
				//state = 100;
				state = 0;
				at_command_data.data[at_command_data.line_count][string_size++] = 0x0A;
				at_command_data.line_count++;
				string_size = 0;
				return STATE_MACHINE_READY_OK;
			}
			else{
				at_error.state_number = 41;
				strcpy(at_error.error_message, "Error at state 41");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 5: {
			if (current_character == 'R'){
				state = 50;
				at_command_data.data[at_command_data.line_count][string_size++] = 'R';
			}
			else{
				at_error.state_number = 5;
				strcpy(at_error.error_message, "Error at state 5");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 50: {
			if (current_character == 'R'){
				state = 51;
				at_command_data.data[at_command_data.line_count][string_size++] = 'R';
			}
			else{
				at_error.state_number = 50;
				strcpy(at_error.error_message, "Error at state 50");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 51: {
			if (current_character == 'O'){
				state = 52;
				at_command_data.data[at_command_data.line_count][string_size++] = 'O';
			}
			else{
				at_error.state_number = 51;
				strcpy(at_error.error_message, "Error at state 51");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 52: {
			if (current_character == 'R'){
				state = 53;
				at_command_data.data[at_command_data.line_count][string_size++] = 'R';
			}
			else{
				at_error.state_number = 52;
				strcpy(at_error.error_message, "Error at state 52");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 53: {
			if (current_character == 0x0D){
				state = 54;
			}
			else {
				at_error.state_number = 53;
				strcpy(at_error.error_message, "Error at state 53");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
		}

		case 54: {
			if (current_character == 0x0A){
				//state = 404;
				state = 0;
				at_command_data.data[at_command_data.line_count][string_size++] = 0x0A;
				at_command_data.line_count++;
				string_size = 0;
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			else {
				at_error.state_number = 54;
				strcpy(at_error.error_message, "Error at state 54");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
		}

		case 6: {
			if (current_character != 0x0D){
				state = 30;
				if(string_size < AT_COMMAND_MAX_LINE_SIZE)
					at_command_data.data[at_command_data.line_count][string_size++] = current_character;
			}
			else
				state = 60;
			break;
		}

		case 60:{
			if (current_character == 0x0A){
				state = 61;
				at_command_data.data[at_command_data.line_count][string_size] = 0x0A;
				string_size = 0;
				at_command_data.line_count++;
			}
			else{
				at_error.state_number = 60;
				strcpy(at_error.error_message, "Error at state 60");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 61: {
			if (current_character != 0x0D){
				state = 6;
			}
			else
				state = 62;
			break;
		}

		case 62: {
			if (current_character == 0x0A){
				state = 63;
			}
			else{
				at_error.state_number = 62;
				strcpy(at_error.error_message, "Error at state 62");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		case 63: {
			if (current_character == 'O'){
				state = 4;
				at_command_data.data[at_command_data.line_count][string_size++] = 'O';
			}
			else if (current_character == 'E'){
				state = 5;
				at_command_data.data[at_command_data.line_count][string_size++] = 'E';
			}
			else{
				at_error.state_number = 34;
				strcpy(at_error.error_message, "Error at state 34");
				return STATE_MACHINE_READY_WITH_ERROR;
			}
			break;
		}

		//case 100: {
			//state = 0;
			//return STATE_MACHINE_READY_OK;
			//break;
		//}

		//case 404: {
			//state = 0;
			//return STATE_MACHINE_READY_WITH_ERROR;
			//break;
		//}
	}

	return STATE_MACHINE_NOT_READY;
}