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

HANDLE hMutex;

const char* thread1Output = "This is output from thread 1";
const char* thread2Output = "This is output from thread 2";
const char* thread3Output = "This is output from thread 3";

DWORD myThread(void *p) {
    int i = 0;
    int threadNum = (int)p;
    const char* txt ="";

    switch(threadNum){
        case 1: txt = thread1Output; break;
        case 2: txt = thread2Output; break;
        case 3: txt = thread3Output; break;
    }

    while (i < 1000000) {
        WaitForSingleObject(hMutex, INFINITE);
        printf("%s\n", txt);
        ReleaseMutex(hMutex);

        i++;
    }
    return 0;
}

int main(void) {
    hMutex = CreateMutex(NULL,FALSE,NULL);
    HANDLE handlers[3] = {NULL};
    handlers [0] = CreateThread(NULL, 0, myThread, (void*)1, 0, NULL);     // thread number 1
    handlers [1] = CreateThread(NULL, 0, myThread, (void*)2, 0, NULL);     // thread number 2
    handlers [2] = CreateThread(NULL, 0, myThread, (void*)3, 0, NULL);     // thread number 3
    WaitForMultipleObjects(3, handlers, TRUE, INFINITE);
    return 0;
}