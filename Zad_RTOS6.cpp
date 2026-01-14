// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t mux;

void Thread2(void* param) {
    vTaskDelay(100);
    if (pdTRUE == xSemaphoreTake(mux, 500)) {
        vTaskDelay(300);
        xSemaphoreGive(mux);
    }
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    TickType_t t = xTaskGetTickCount();
    if (pdTRUE == xSemaphoreTake(mux, 500)) {
        vTaskDelay(500);
        xSemaphoreGive(mux);
    }
    printf("T = %d", xTaskGetTickCount() - t);
    vTaskDelete(NULL);
}

int main(void) {
    mux = xSemaphoreCreateMutex();
    xTaskCreate(Thread1, "thread1", 512, NULL, 3, NULL);
    xTaskCreate(Thread2, "thread2", 512, NULL, 5, NULL);
    vTaskStartScheduler();
}
Odp:
T=500

1. Thread2 startuje jako pierwszy i blokuje sie na vTaskDelay(100)
2. Uruchamia się Thread1 i ustala T=0, zabiera mutexa i ma go aż do T=500
3. T=100, Thread2 próbuje wziąć mutexa ale jest zajety juz przez Thread1
4. T=500, Thread1 oddaje mutexa i następuje wywłaszczenie - start Thread2
5. T=500, Thread2 rezerwuje mutexa az do T=800 i oddaje go poczym usuwa się
6. Thread1 wraca i wypisuje T=500
