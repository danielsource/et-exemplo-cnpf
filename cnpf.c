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
  "Aperte q para sair | Press q to exit"
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
  int value;

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
    expression = get_user_line();
    
    /* Se usuário digitar 'q', finalize o programa (quit). */
    if (strcmp(expression, "q") == 0) {
      break;
    }

    /* Execute a calculadora 'calc': */
    if (calc(expression, &value)) {
      printf("%d\n", value);
    } else {
      puts("<Erro de sintaxe>");
    }
  }
  
  return 0;
}