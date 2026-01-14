// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t sem;

void Thread2(void* param) {
    vTaskDelay(600);
    xSemaphoreGive(sem);
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    TickType_t t = xTaskGetTickCount();
    vTaskDelay(200);
    xSemaphoreTake(sem, 400);
    printf("T = %d", xTaskGetTickCount() - t);
    vTaskDelete(NULL);
}

int main(void) {
    sem = xSemaphoreCreateBinary();
    xTaskCreate(Thread1, "thread1", 512, NULL, 5, NULL);
    xTaskCreate(Thread2, "thread2", 512, NULL, 3, NULL);
    vTaskStartScheduler();
}