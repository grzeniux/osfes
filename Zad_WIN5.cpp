// Budowanie kodu to skrót CTRL+B a uruchomić go można klikając z menu kontekstowego opcję 
// "Run As Local C/C++ Application". Dany jest poniższy fragment programu, korzystający z systemu Windows.

// Zmodyfikuj poniższy kod w ten sposób, aby:

// zamiast obecnie wypisywanego tekstu każdy wątek N wypisywał łańcuch tekstowy threadNOutput, 
// gdzie N to numer wątku (1,2 lub 3), ale nie duplikuj funkcji wątku (ma być jedna)

// wywołanie printf nie mogło być przerwane przez inne wywołanie printf wykonywane 
// z poziomu innego (bliźniaczego), tworzonego w tym programie wątku,

// program kończył się niezwłocznie po zakończeniu działania wszystkich 3 instancji wątków, 
// zamiast (tak jak to jest obecnie) po 1000 ms.


#include <windows.h>
#include <stdio.h>

const char* thread1Output = "This is output from thread 1";
const char* thread2Output = "This is output from thread 2";
const char* thread3Output = "This is output from thread 3";

DWORD myThread(void *p) {
    int i = 0;
    while (i < 1000000) {
        printf("This is some thread output\n");
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