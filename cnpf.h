#pragma once

/* calc.c */
bool calc(const char *expression, int *value);

/* calc_stack.c */
#define CALC_STACK_SIZE 256
extern int calc_stack[CALC_STACK_SIZE];
extern int calc_top;
bool calc_push(int value);
bool calc_pop(int *value);

/* util.c */
void fatal_error(const char *message);
char *get_user_line(int *length);