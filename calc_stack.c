#include <stdbool.h>

#include "cnpf.h"

/* Pilha para armazenar operandos. */
int calc_stack[CALC_STACK_SIZE];
int calc_top = -1;

/* Empilhar valor na pilha da calculadora. */
bool calc_push(int value)
{
  if (calc_top < CALC_STACK_SIZE-1) {
    calc_stack[++calc_top] = value;
    return true;
  } else {
    return false;
  }
}

/* Desempilhar valor na pilha da calculadora. */
bool calc_pop(int *value)
{
  if (calc_top >= 0)
  {
    *value = calc_stack[calc_top--];
    return true;
  } else {
    return false;
  }
}