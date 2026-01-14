// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.
SemaphoreHandle_t mux;
void Thread2(void* param) {
    vTaskDelay(2000);
    if (pdTRUE == xSemaphoreTake(mux, 5000)) {
        vTaskDelay(3000);
        xSemaphoreGive(mux);
    }
    vTaskDelete(NULL);
}
void Thread1(void* param) {
    TickType_t t = xTaskGetTickCount();
    vTaskDelay(1000);
    if (pdTRUE == xSemaphoreTake(mux, 5000)) {
        vTaskDelay(1000);
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
T = 2000

1. Thread2 startuje jako pierwszy bo ma wyższy priorytet
2. Thread2 jest uśpiony aż do T=2000
3. T=0 startuje Thread1 i ustawia czas T=0, nastepnie jest uspiony az do T=1000
4. T=1000 startuje Thread1 i bierze mutexa, czeka az do T=2000 i oddaje mutex i wypisuje T=2000
5. T=2000 Startuje Thread2, bierze mutexa i czeka az do T=5000 i oddaje mutex i usuwa się



