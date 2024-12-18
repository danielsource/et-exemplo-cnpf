const char *const banner =
  "cnpf: calculadora em notação pós-fixada\n"
  "=======================================\n"
  "'cnpf' é uma simples calculadora de\n"
  "linha de comando que implementa as 4\n"
  "operações aritméticas básicas (+ - * /)\n"
  "em inteiros na notação pós-fixada\n"
  "(também conhecida como 'Reverse Polish\n"
  "Notation').\n"
  "=======================================\n"
  "DIGITE 'q' PARA SAIR | DIGITE 'e' PARA EXEMPLOS"
;

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "cnpf.h"

#include "util.c"
#include "calc_stack.c"
#include "calc.c"

int main(int argc, char **argv)
{
  char *expression;
  int expression_length;
  long value;
  int i;

  setlocale(LC_ALL, "pt_BR");

  if (argc == 2 && strcmp(argv[1], "-q") == 0) {
    /* Desativar 'banner' inicial ao passar a opção "-q". */
  } else if (argc < 2) {
    puts(banner);
  } else {
    fatal_error("Utilização: cnpf [-q]");
  }
  
  while (true) {
    /* Obtenha a expressão aritmética do usuário. */
    expression = get_user_line(&expression_length);

    /* Remova espaços desnecessários no *início* da expressão. */
    while (expression[0] == ' ') {
      ++expression;
      --expression_length;
    }

    /* Remova espaços desnecessários no *final* da expressão. */
    for (i = expression_length-1; expression[i] == ' '; --i) {
      expression[i] = '\0';
      --expression_length;
    }

    /* Se usuário não digitar nada, prossiga para a próxima leitura. */
    if (expression_length == 0) {
      continue;
    }
    /* Se usuário digitar 'q', finalize o programa (quit). */
    else if (strcmp(expression, "q") == 0) {
      break;
    }
    /* Se usuário digitar 'e', exiba exemplos da calculadora. */
    else if (strcmp(expression, "e") == 0) {
      putchar('\n');
      puts("Expressão convencional: 2 + 2");
      puts("Expressão 'cnpf':       2 2 +");
      putchar('\n');
      puts("Expressão convencional: (4 + 6) / 2");
      puts("Expressão 'cnpf':       4 6 + 2 /");
      putchar('\n');
      puts("Expressão convencional: ((4 * 2) - (5 * 2)) / (2 * -1)");
      puts("Expressão 'cnpf':       4 2 * 5 2 * - 2 -1 * /");
      putchar('\n');
      puts("Note que na notação pós-fixada não é usado parênteses.");
      puts("Obs: neste programa, espaços entre operandos ou operadores são obrigatórios!\n");
      continue;
    }

    /* Execute a calculadora 'calc': */
    if (calc(expression, &value)) {
      printf("%ld\n", value);
    } else {
      puts("<Erro de sintaxe>");
    }
  }
  
  return 0;
}