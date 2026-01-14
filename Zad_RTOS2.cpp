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

1. Thread2 ma wyższy priorytet więc uruchomi się jako pierwszy i wpadnie w vTaskDelay(100)
2. Wtedy Thread1 przejmuje zadanie i ustala czas T=0, zajmuje mutexa i ma go aż do T=500
3. T=100, Thread2 sie budzi i próbuje wziac mutex ale jest zajety przez Thread1 wiec Thread2 pozostaje blocked
4. T=500, Thread1 oddaje mutex i wypisuje T=500 i usuwa się
5. T=500, Thread2 zabiera mutex i trzyma go aż do T=800, nastepnie oddaje i usuwa się

