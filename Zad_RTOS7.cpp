// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t mux;

void Thread2(void* param) {
    vTaskDelay(100);
    if (pdTRUE == xSemaphoreTake(mux, 800)) {
        vTaskDelay(500);
        xSemaphoreGive(mux);
    }
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    TickType_t t = xTaskGetTickCount();
    vTaskDelay(300);
    if (pdTRUE == xSemaphoreTake(mux, 500)) {
        vTaskDelay(100);
        xSemaphoreGive(mux);
    }
    printf("T = %d", xTaskGetTickCount() - t);
    vTaskDelete(NULL);
}

int main(void) {
    mux = xSemaphoreCreateMutex();
    xTaskCreate(Thread1, "thread1", 512, NULL, 5, NULL); // Priorytet 5
    xTaskCreate(Thread2, "thread2", 512, NULL, 3, NULL); // Priorytet 3
    vTaskStartScheduler();
}