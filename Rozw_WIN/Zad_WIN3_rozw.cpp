// Dany jest poniższy fragment programu, korzystający z systemu Windows. Zmodyfikuj go w ten sposób, aby:

// wywołanie printf nie mogło być przerwane przez inne wywołanie printf wykonywane 
// z poziomu innego (bliźniaczego), tworzonego w tym programie wątku,

// program kończył się niezwłocznie po zakończeniu działania wszystkich 3 wątków, 
// zamiast (tak jak to jest obecnie) po 1000 ms.
#include <windows.h>
#include <stdio.h>
HANDLE hMutex;

DWORD myThread1(void *p) {
    int i = 0;
    while (i < 1000000) {
        WaitForSingleObject(hMutex,INFINITE);
        printf("%d, This is thread 1 output\n", i++);
        ReleaseMutex(hMutex);
    }
    return 0;
}
DWORD myThread2(void *p) {
    int i = 0;
    while (i < 1000000) {
         WaitForSingleObject(hMutex,INFINITE);
        printf("%d, This is thread 2 output\n", i++);
        
        ReleaseMutex(hMutex);
    }
    return 0;
}
DWORD myThread3(void *p) {
    int i = 0;
    while (i < 1000000) {
         WaitForSingleObject(hMutex,INFINITE);
        printf("%d, This is thread 3 output\n", i++);
        ReleaseMutex(hMutex);
    }
    return 0;
}
int main(void) {
    hMutex = CreateMutex(NULL, FALSE,NULL);
    HANDLE handlers[3] = {NULL};
    handlers[0] = CreateThread(NULL, 0, myThread1, NULL, 0, NULL);     // thread number 1
    handlers[1] = CreateThread(NULL, 0, myThread2, NULL, 0, NULL);     // thread number 2
    handlers[2] = CreateThread(NULL, 0, myThread3, NULL, 0, NULL);     // thread number 3
    //Sleep(1000);
    WaitForMultipleObjects(3, handlers, TRUE, INFINITE);
    return 0;
}