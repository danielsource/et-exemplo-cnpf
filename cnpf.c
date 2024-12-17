const char *const banner =
  "cnpf: calculadora em notação pós-fixada\n"
  "=======================================\n"
  "'cnpf' é uma simples calculadora de linha de comando que implementa as\n"
  "4 operações aritméticas básicas (+ - * /) em inteiros na notação\n"
  "pós-fixada (também conhecida como 'Reverse Polish Notation').\n"
  "=======================================\n"
;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define BUFFER_SIZE 512

/* Imprima mensagem de erro e finalize a execução com código de falha (1). */
void fatal_error(const char *message)
{
  fputs(message, stderr);
  exit(1);
}

/* Obtenha caracteres da linha de entrada. */
char *get_user_line(void)
{
  static char buffer[BUFFER_SIZE];
  int i;
  
  fputs("> ", stdout);
  
  if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
    fatal_error("fgets() falhou.\n");
  }
  
  /* Remova a "nova linha" do final da cadeia. */
  for (i = 0; buffer[i] != '\0'; ++i) {
    if (buffer[i] == '\n') {
      buffer[i] = '\0';
      break;
    }
  }
  
  return buffer;
}

int main(int argc, char **argv)
{
  char *expression;
  
  setlocale(LC_ALL, "pt_BR");

  if (argc == 2 && strcmp(argv[1], "-q") == 0) {
    /* Desativar 'banner' inicial ao passar a opção "-q". */
  } else if (argc < 2) {
    fputs(banner, stdout);
  } else {
    fatal_error("Utilização: cnpf [-q]\n");
  }
  
  while (true) {
    /* Obtenha a expressão aritmética do usuário. */
    expression = get_user_line();
    
    /* Se usuário digitar 'q', finalize o programa (quit). */
    if (strcmp(expression, "q") == 0) {
      break;
    }
  }
  
  return 0;
}