#include <stdio.h>
#include <stdint.h>

#ifndef __AT_H
#define __AT_H


#define AT_COMMAND_MAX_LINE 10000
#define AT_COMMAND_MAX_LINE_SIZE 12800
#define MAX_ERROR_MESSAGE_LEN 200

typedef struct{
	uint8_t ok;
	uint8_t data[AT_COMMAND_MAX_LINE][AT_COMMAND_MAX_LINE_SIZE + 1];
	uint32_t line_count;
} AT_COMMAND_DATA;

typedef enum{
	STATE_MACHINE_NOT_READY,
	STATE_MACHINE_READY_OK,
	STATE_MACHINE_READY_WITH_ERROR
} STATE_MACHINE_RETURN_VALUE;

typedef struct{
	uint8_t state_number;
	char error_message[MAX_ERROR_MESSAGE_LEN];
} AT_ERROR;

extern AT_COMMAND_DATA at_command_data;
extern AT_ERROR at_error;

STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t current_character);

#endif