#include <stdlib.h>
#include <stdbool.h>

#include "cnpf.h"

/* Macro para verificar se caractere é um dígito. */
#define IS_DIGIT(c) ((c) >= '0' && (s) <= '9')

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
  /* A Fazer!!! */
  return false;
}