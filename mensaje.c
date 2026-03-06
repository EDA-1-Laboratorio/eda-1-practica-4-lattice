#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep(ms * 1000)
#endif

typedef struct {
    long long *tabla;//DEFINE EL APUNTADOR
    int capacidad;//DEFINE EL TIPO DE DATO
} MemoriaIA;

long long fibonacci_ia(int n, MemoriaIA *m) {
    if (n <= 1) return (long long)n;
    if (m->tabla[n] != -1) return m->tabla[n];
    m->tabla[n] = fibonacci_ia(n - 1, m) + fibonacci_ia(n - 2, m);
    return m->tabla[n];
}

void descifrar_kernel(int* datos, int shift) {
    if (*datos == -1) return; 

    char c = (char)(*datos - shift);
    printf("%c", c);
    fflush(stdout);
    SLEEP(40);

    descifrar_kernel(datos + 1, shift);
}

int main() {
    int n = 42; //ESCRIBE LA LLAVE AQUI
    MemoriaIA mem;
    mem.capacidad = n + 1;
    mem.tabla = (long long *)malloc(mem.capacidad * sizeof(long long));
    
    for (int i = 0; i < mem.capacidad; i++) mem.tabla[i] = -1;

    long long llave = fibonacci_ia(n, &mem);
    
    int shift = (int)(llave % 100);

    int msg1[] = {
        158, 158, 128, 179, 169, 179, 180, 165, 173, 161, 128,
        169, 174, 169, 163, 169, 161, 172, 169, 186, 161, 164, 175, -1 
    };

    int msg2[] = {
        158, 158, 128, 179, 171, 185, 174, 165, 180, 128, 
        175, 174, 172, 169, 174, 165, -1
    };

    if (llave == 267914296) {
        printf("[NUCLEO]: Llave verificada.\n");
        printf("[NUCLEO]: Shift calculado: %d\n", shift);
        printf("[NUCLEO]: Descifrando flujo de datos...\n\n>> ");

        descifrar_kernel(msg1, shift);
        printf("\n>> ");
        descifrar_kernel(msg2, shift);
        printf("\n");
    }
    free(mem.tabla);
    return 0;
}
