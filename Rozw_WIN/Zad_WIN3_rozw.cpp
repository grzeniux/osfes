// Dany jest poniższy fragment programu, korzystający z systemu Windows. Zmodyfikuj go w ten sposób, aby:

// wywołanie printf nie mogło być przerwane przez inne wywołanie printf wykonywane 
// z poziomu innego (bliźniaczego), tworzonego w tym programie wątku,

// program kończył się niezwłocznie po zakończeniu działania wszystkich 3 wątków, 
// zamiast (tak jak to jest obecnie) po 1000 ms.


#include <windows.h>
#include <stdio.h>

DWORD myThread1(void *p) {
    int i = 0;
    while (i < 1000000) {
        printf("%d, This is thread 1 output\n", i++);
    }
    return 0;
}

DWORD myThread2(void *p) {
    int i = 0;
    while (i < 1000000) {
        printf("%d, This is thread 2 output\n", i++);
    }
    return 0;
}

DWORD myThread3(void *p) {
    int i = 0;
    while (i < 1000000) {
        printf("%d, This is thread 3 output\n", i++);
    }
    return 0;
}

int main(void) {
    // thread number 1
    CreateThread(NULL, 0, myThread1, NULL, 0, NULL);
    // thread number 2
    CreateThread(NULL, 0, myThread2, NULL, 0, NULL);
    // thread number 3
    CreateThread(NULL, 0, myThread3, NULL, 0, NULL);
    Sleep(1000);
    return 0;
}