// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

static volatile int run = 1;

void Thread(void* param) {
    volatile int counter = 0;
    while (run) {
        counter++;
        if (counter == 1000) {
            run = 0;
        }
    }
    printf("counter = %d\n", counter);
    vTaskDelete(NULL);
}

int main(void) {
    xTaskCreate(Thread, "thread1", 512, NULL, 2, NULL);
    xTaskCreate(Thread, "thread2", 512, NULL, 4, NULL);
    vTaskStartScheduler();
}