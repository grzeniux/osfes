// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t sem;

void Thread2(void* param) {
    vTaskDelay(2000);
    xSemaphoreGive(sem);
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    static volatile int i;
    TickType_t t = xTaskGetTickCount();
    for (i = 0; i < 1000; i++) {
        if (pdTRUE == xSemaphoreTake(sem, 0)) {
            printf("OK,");
            i = 1000;
        } else {
            vTaskDelay(1);
        }
    }
    printf("T = %d", xTaskGetTickCount() - t);
    vTaskDelete(NULL);
}

int main(void) {
    sem = xSemaphoreCreateBinary();
    xTaskCreate(Thread1, "thread1", 512, NULL, 3, NULL);
    xTaskCreate(Thread2, "thread2", 512, NULL, 3, NULL);
    vTaskStartScheduler();
}