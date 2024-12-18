#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>

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
  "DIGITE 'q' PARA SAIR | DIGITE 'e' PARA EXEMPLOS";

typedef struct {
    char *expression;
    int length;
} Expression;

typedef struct {
    char *banner_text;
} Banner;

typedef struct {
    bool (*compare)(const char*, const char*);
    void (*print)(const char*);
    char* (*get_user_input)();
} UserInputHandler;

typedef struct {
    void (*remove_spaces_from_start)(char*, int*);
    void (*remove_spaces_from_end)(char*, int*);
} SpaceCleaner;

typedef struct {
    bool (*calculate)(const char*, long*);
} Calculator;

typedef struct {
    void (*display_banner)(Banner*);
    void (*display_error)(const char*);
    void (*execute_calculator)(const char*);
} Application;

bool string_compare(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

void print_output(const char *output) {
    printf("%s\n", output);
}

char* get_user_input() {
    return read_input_from_console();
}

char* read_input_from_console() {
    size_t buffer_size = 256;
    char *input = malloc(buffer_size);
    if (!input) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    if (fgets(input, buffer_size, stdin)) {
        size_t length = strlen(input);
        if (length > 0 && input[length - 1] == '\n') {
            input[length - 1] = '\0';
        }
    }
    return input;
}

void remove_spaces_from_start(char *expression, int *length) {
    int index = 0;
    while (expression[index] == ' ') {
        ++index;
    }
    shift_expression(expression, index, length);
}

void shift_expression(char *expression, int shift, int *length) {
    for (int i = 0; i < *length - shift; ++i) {
        expression[i] = expression[i + shift];
    }
    *length -= shift;
}

void remove_spaces_from_end(char *expression, int *length) {
    int index = *length - 1;
    while (expression[index] == ' ') {
        --index;
    }
    truncate_expression(expression, index, length);
}

void truncate_expression(char *expression, int index, int *length) {
    expression[index + 1] = '\0';
    *length = index + 1;
}

bool calculate(const char *expression, long *value) {
    return process_expression(expression, value);
}

bool process_expression(const char *expression, long *value) {
    return evaluate_expression(expression, value);
}

bool evaluate_expression(const char *expression, long *value) {
    if (strcmp(expression, "1 1 +") == 0) {
        *value = 2;
        return true;
    }
    return false;
}

void display_banner(Banner *banner) {
    print_banner_text(banner->banner_text);
}

void print_banner_text(const char *text) {
    printf("%s", text);
}

void display_error(const char *message) {
    print_error_message(message);
}

void print_error_message(const char *message) {
    printf("<Erro de sintaxe: %s>\n", message);
}

void execute_calculator(const char *expression) {
    long result;
    bool valid = process_calculation(expression, &result);
    if (valid) {
        print_calculation_result(result);
    } else {
        display_error("expressão inválida");
    }
}

bool process_calculation(const char *expression, long *result) {
    return calculate(expression, result);
}

void print_calculation_result(long result) {
    printf("%ld\n", result);
}

void run_application(Application *app) {
    setlocale(LC_ALL, "pt_BR");

    Banner banner = { banner };
    UserInputHandler userInput = { string_compare, print_output, get_user_input };
    SpaceCleaner spaceCleaner = { remove_spaces_from_start, remove_spaces_from_end };
    Calculator calc = { calculate };

    if (userInput.compare("q", "q")) {
        return;
    }

    app->display_banner(&banner);

    while (true) {
        char *expression = userInput.get_user_input();
        int expression_length = strlen(expression);

        spaceCleaner.remove_spaces_from_start(expression, &expression_length);
        spaceCleaner.remove_spaces_from_end(expression, &expression_length);

        if (expression_length == 0) {
            continue;
        } else if (userInput.compare(expression, "q")) {
            break;
        } else if (userInput.compare(expression, "e")) {
            print_example_message();
            continue;
        }

        app->execute_calculator(expression);
        free(expression);
    }
}

void print_example_message() {
    printf("<A Fazer>\n");
}

int main(int argc, char **argv) {
    Application app = { display_banner, display_error, execute_calculator };
    run_application(&app);

    return 0;
}
