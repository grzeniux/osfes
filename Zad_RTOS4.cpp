// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj co program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

void Thread2(void* param) {
    volatile unsigned int i;
    for (i = 0; i < 1000000; i++) {
        i++; i--;
    }
    printf("Thread2\n");
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    xTaskCreate(Thread2, "thread2", 512, NULL, 4, NULL);
    taskYIELD();
    printf("Thread1\n");
    vTaskDelete(NULL);
}

int main(void) {
    xTaskCreate(Thread1, "thread1", 512, NULL, 2, NULL);
    vTaskStartScheduler();
}

Odp:
Thread2
Thread1

1. Thread1 startuje i odrazu woła Thread2, który ma wyzszy priorytet wiec wykonuje sie Thread2
2. Mamy pętle, która nas nie blokuje, po wykonaniu pętli wypisujemy "Thread2" i usuwa wątek
3. Printujemy "Thread1"


