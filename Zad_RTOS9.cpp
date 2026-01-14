// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
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