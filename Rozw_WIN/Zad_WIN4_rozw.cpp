// Dany jest poniższy fragment programu, korzystający z systemu Windows. 
// Program otwiera plik a następnie przekazuje uchwyt pliku do 3 wątków. 
// W każdym wątku następuje odczyt pliku linia po linii i wypisanie na standardowe wyjście. 
// Zmodyfikuj program w ten sposób, aby:

// wywołanie fgets i fputs w wątku nie mogło być przerwane przez inne wywołanie tych funkcji wykonywane 
// z poziomu innego (bliźniaczego), tworzonego w tym programie wątku,

// program kończył się niezwłocznie po zakończeniu działania wszystkich 3 wątków, 
// zamiast (tak jak to jest obecnie) po 3000 ms.

#include <windows.h>
#include <stdio.h>
HANDLE hMutex;
DWORD myThread(void *p) {
    char str[1024];
    // while not end of file
    while (!feof(p)) {
        // get single line of text
        WaitForSingleObject(hMutex, INFINITE);
        if (NULL != fgets(str, sizeof(str), p)) {
            // print line to standard output
            fputs(str, stdout);
            ReleaseMutex(hMutex);
        }
    }
    return 0;
}
int main(void) {

    hMutex = CreateMutex(NULL,FALSE,NULL);
    HANDLE handlers[3] = {NULL};
    // open text file
    FILE * pFile = fopen("input.txt", "r");
    // check if file was opened
    if (NULL != pFile) {
        handlers [0] = CreateThread(NULL, 0, myThread, pFile, 0, NULL);         // thread number 1
        handlers [1] = CreateThread(NULL, 0, myThread, pFile, 0, NULL);         // thread number 2
        handlers [2] = CreateThread(NULL, 0, myThread, pFile, 0, NULL);         // thread number 3
        //Sleep(3000);
        WaitForMultipleObjects(3, handlers, TRUE,INFINITE);
        // close file
        fclose(pFile);
    } else {
        puts("Unable to open input.txt");
    }
    return 0;
}