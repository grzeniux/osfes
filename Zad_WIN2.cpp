// Dany jest poniższy fragment programu, korzystający z systemu Windows. Zmodyfikuj 
// go w ten sposób, aby:

// operacja printf w wątku wyświetlała dodatkowo numer wątku, z poziomu którego 
// jest wykonywana (ale nie duplikuj funkcji wątku),

// program kończył się niezwłocznie po zakończeniu działania wszystkich 3 instancji wątków, 
// zamiast (tak jak to jest obecnie) po 1000 ms.

#include <windows.h>
#include <stdio.h>

DWORD myThread(void *p) {
    int i = 0;
    while (i < 1000000) {
        printf("%d, This is some thread output\n", i++);
    }
    return 0;
}

int main(void) {
    CreateThread(NULL, 0, myThread, NULL, 0, NULL);
    CreateThread(NULL, 0, myThread, NULL, 0, NULL);
    CreateThread(NULL, 0, myThread, NULL, 0, NULL);
    Sleep(1000);
    return 0;
}