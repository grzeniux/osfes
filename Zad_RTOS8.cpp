// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

void Thread2(void* param) {
    static volatile unsigned int i;
    for (i = 0; i < 9999999; i++) {
        i++; i--;
    }
    printf("Thread2\n");
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    xTaskCreate(Thread2, "thread2", 512, NULL, 2, NULL);
    printf("Thread1\n");
    vTaskDelete(NULL);
}

int main(void) {
    xTaskCreate(Thread1, "thread1", 512, NULL, 4, NULL);
    vTaskStartScheduler();
}
Odp:
Thread1
Thread2

1. Startuje Thread1, który woła Thread2 o mniejszym priorytecie więc jest kontynuowany Thread1
2. Printujemy Thread1 i usuwamy wątek
3. Wracamy do Thread2, wykonuje się pętla i printujemy Thread2