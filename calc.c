#include <stdlib.h>
#include <stdbool.h>

#include "cnpf.h"

/* Macro para verificar se caractere é um dígito. */
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

/* A função 'calc' recebe uma cadeia de caracteres de uma expressão e um
 * ponteiro para um inteiro usado para armazenar o valor do cálculo.
 * Retorna 'true' se realizar o cálculo corretamente e 'false' ao encontrar
 * algum erro de sintaxe na expressão ou divisão por zero.
 *
 * A expressão recebida por 'calc' segue vagamente essa gramática em BNF:
 *   <expression> ::= <integer>    " "+ <integer>    " "+ <operator> |
 *                    <integer>    " "+ <expression> " "+ <operator> |
 *                    <expression> " "+ <integer>    " "+ <operator> |
 *                    <expression> " "+ <expression> " "+ <operator>
 *   <operator>   ::= "+" | "-" | "*" | "/"
 *   <integer>    ::= "-"? ("0" | [1-9] [0-9]*)
 */
bool calc(const char *expression, int *value)
{
  const char *s;
  char *n_end;
  int n;

  /* Comece com a pilha na posição inicial (vazia). */
  calc_top = -1;

  s = expression;
  *value = 0;

  /* Processe a expressão até chegar no seu fim: */
  while (s[0] != '\0') {

    /* Caso encontre um espaço: */
    if (s[0] == ' ') {
      /* Ignore o espaço e vá para o próximo caractere. */
      ++s;
      continue;
    }

    /* Caso encontre um inteiro: */
    if (IS_DIGIT(s[0]) || (s[0] == '-' && IS_DIGIT(s[1]))) {
      /* Tente converter os caracteres para um valor inteiro: */
      n = strtol(s, &n_end, 10);

      /* Finalize com erro caso encontre um caractere inesperado no final do número: */
      if (n_end[0] != ' ') {
        return false;
      }

      /* Finalize com erro caso não tenha mais espaço na pilha (veja 'CALC_STACK_SIZE'): */
      if (!calc_push(n)) {
        return false;
      }

      /* Pule todos os caracteres já processados por 'strtol': */
      s = n_end;
      continue;
    }

    /* Tente processar um operador: */
    switch (s[0]) {
    case '+': if (!0 /* A Fazer */) return false; break;
    case '-': if (!0 /* A Fazer */) return false; break;
    case '*': if (!0 /* A Fazer */) return false; break;
    case '/': if (!0 /* A Fazer */) return false; break;
    default: /* Finalize com erro em um caractere inesperado: */ return false;
    }

    ++s;
  }

  return true;
}