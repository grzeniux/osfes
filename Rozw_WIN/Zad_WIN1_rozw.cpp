// Dany jest poniższy fragment programu, korzystający z systemu Windows. Zmodyfikuj go w ten sposób, aby:

// wywołanie printf nie mogło być przerwane przez inne wywołanie printf 
// wykonywane z poziomu innego (bliźniaczego), tworzonego w tym programie wątku,

// operacja printf w wątku wyświetlała dodatkowo numer wątku, z poziomu 
// którego jest wykonywana (ale nie duplikuj funkcji wątku),
#include <windows.h>
#include <stdio.h>
HANDLE hMutex;

DWORD myThread(void *p) {
    int threadNum = (int)p;
    int i = 0;
    while (i < 1000000) {
        WaitForSingleObject(hMutex,INFINITE);
        printf("Thread num:%d, %d, This is some thread output\n", threadNum ,i++);
        ReleaseMutex(hMutex);
    }
    return 0;
}
int main(void) {
    hMutex = CreateMutex(NULL, FALSE,NULL);
    CreateThread(NULL, 0, myThread, (void*)1, 0, NULL);     // thread number 1
    CreateThread(NULL, 0, myThread, (void*)2, 0, NULL);     // thread number 2
    CreateThread(NULL, 0, myThread, (void*)3, 0, NULL);     // thread number 3
    Sleep(1000);
    return 0;
}