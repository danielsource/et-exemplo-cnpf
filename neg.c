#include <stdio.h>

// Função para negar um número
int negarNumero(int numero) {
    return -numero;
}

int main() {
    int numero, resultado;

    printf("Digite um numero: ");
    scanf("%d", &numero);

    // Chama a função para calcular o número negado
    resultado = negarNumero(numero);

    printf("O numero negado e: %d\n", resultado);

    return 0;
}
