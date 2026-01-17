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
Odp:
T = 700

1. Thread1 ma wyższy priorytet wiec startuje i ustala czas T=0, jest w stanie blocked aż do T=300
2. Thread2 startuje i jest w stanie blocked aż do T=100
3. T=100, Thread2 rezerwuje mutexa i ma go aż do T=600
4. T=300, Thread1 budzi się i próbuje wziąć mutexa ale jest zajęty więc czeka max 500 (czyli do T=800)
5. T=600, Thread1 przejmuje mutexa od Thread2 i ma  go aż do T=700 poczym go oddaje i wypisuje T=700
