// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t mux;

void Thread2(void* param) {
    if (pdTRUE == xSemaphoreTakeRecursive(mux, 5000)) {
        vTaskDelay(3000);
        xSemaphoreGiveRecursive(mux);
    }
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    TickType_t t = xTaskGetTickCount();
    vTaskDelay(1000);
    if (pdTRUE == xSemaphoreTakeRecursive(mux, 5000)) {
        vTaskDelay(1000);
        xSemaphoreGiveRecursive(mux);
    }
    printf("T = %d", xTaskGetTickCount() - t);
    vTaskDelete(NULL);
}

int main(void) {
    mux = xSemaphoreCreateRecursiveMutex();
    xTaskCreate(Thread1, "thread1", 512, NULL, 3, NULL);
    xTaskCreate(Thread2, "thread2", 512, NULL, 3, NULL);
    vTaskStartScheduler();
}