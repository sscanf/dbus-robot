#include <stdio.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <controller> <gpio>\n", argv[0]);
        return 1;  
    }

    // Convertir los argumentos de cadena a números enteros
    int controller = atoi(argv[1]);
    int gpio = atoi(argv[2]);

    int res = 480 - 32 * controller + gpio;

    printf("resulado = %d\n", res);

    return 0;  // Termina el programa exitosamente
}
