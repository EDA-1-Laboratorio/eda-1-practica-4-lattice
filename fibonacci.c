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
    long long *tabla; // DEFINE LA VARIABLE APUNTADORA AL SIGUIENTE ELEMENTO
    int capacidad; // DEFINE LA VARIABLE QUE CONTIENE EL DATO EN CADA ESPACIO DE LA ESTRUCTURA
} MemoriaIA;

long long fibonacci_ia(int n, MemoriaIA *m) {
    if (n <= 1) return (long long)n;

    // Si ya está en el Heap, lo devolvemos
    if (m->tabla[n] != -1) return m->tabla[n];

    // Calculamos y guardamos
    m->tabla[n] = fibonacci_ia(n - 1, m) + fibonacci_ia(n - 2, m);
    return m->tabla[n];
}

void imprimir_poco_a_poco(const char *mensaje) {
    for (int i = 0; mensaje[i] != '\0'; i++) {
        printf("%c", mensaje[i]);
        fflush(stdout);
        SLEEP(60);
    }
}

int main() {
    int n = 42; // INGRESA LA LLAVE DE LAS INSTRUCCIONES
    MemoriaIA mem;

    mem.capacidad = n + 1;
    mem.tabla = (long long *)malloc(mem.capacidad * sizeof(long long));
    for (int i = 0; i < mem.capacidad; i++) mem.tabla[i] = -1;

    imprimir_poco_a_poco("[SISTEMA]: Accediendo al núcleo de memoria dinámica...\n");
    imprimir_poco_a_poco("[SISTEMA]: Calculando secuencia de Fibonacci (N=42)...\n\n");
    SLEEP(500);

    long long resultado = fibonacci_ia(n, &mem);

    printf("ESTADO DEL HEAP:\n----------------\n");
    for (int i = 0; i <= n; i++) {
        printf("F(%02d): %-12lld ", i, mem.tabla[i]);
        if ((i + 1) % 3 == 0) printf("\n"); // Formato en columnas
        
        fflush(stdout);
        SLEEP(30);
    }

    printf("\n\n--------------------------------------\n");
    char frase_final[100];
    sprintf(frase_final, ">>> LLAVE GENERADA EN F(%d): %lld\n", n, resultado);
    imprimir_poco_a_poco(frase_final);
    imprimir_poco_a_poco("--------------------------------------\n");

    // 5. Limpieza
    free(mem.tabla);
    return 0;
}
