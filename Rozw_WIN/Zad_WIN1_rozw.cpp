// Dany jest poniższy fragment programu, korzystający z systemu Windows. Zmodyfikuj go w ten sposób, aby:

// wywołanie printf nie mogło być przerwane przez inne wywołanie printf 
// wykonywane z poziomu innego (bliźniaczego), tworzonego w tym programie wątku,

// operacja printf w wątku wyświetlała dodatkowo numer wątku, z poziomu 
// którego jest wykonywana (ale nie duplikuj funkcji wątku),


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
    // thread number 1
    CreateThread(NULL, 0, myThread, NULL, 0, NULL);
    // thread number 2
    CreateThread(NULL, 0, myThread, NULL, 0, NULL);
    // thread number 3
    CreateThread(NULL, 0, myThread, NULL, 0, NULL);
    Sleep(1000);
    return 0;
}

