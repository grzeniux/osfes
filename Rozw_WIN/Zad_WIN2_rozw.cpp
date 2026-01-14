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

    int threadNum = (int)p;
    while (i < 1000000) {
        printf("Thread Num: %d, %d, This is some thread output\n", threadNum ,i++);
    }
    return 0;
}

int main(void) {
    HANDLE handlers[3] = {NULL};
    handlers[0] = CreateThread(NULL, 0, myThread, (void*)1, 0, NULL);     // thread number 1
    handlers[1] = CreateThread(NULL, 0, myThread, (void*)2, 0, NULL);     // thread number 2
    handlers[2] = CreateThread(NULL, 0, myThread, (void*)3, 0, NULL);     // thread number 3
    //Sleep(1000);
    WaitForMultipleObjects(3, handlers,TRUE,INFINITE);
    return 0;
}