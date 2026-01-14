// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t sem;

void Thread2(void* param) {
    vTaskDelay(3000);
    xSemaphoreGive(sem);
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    TickType_t t = xTaskGetTickCount();
    vTaskDelay(1000);
    xSemaphoreTake(sem, 1000);
    printf("T = %d", xTaskGetTickCount() - t);
    vTaskDelete(NULL);
}

int main(void) {
    sem = xSemaphoreCreateBinary();
    xTaskCreate(Thread1, "thread1", 512, NULL, 5, NULL);
    xTaskCreate(Thread2, "thread2", 512, NULL, 3, NULL);
    vTaskStartScheduler();
}