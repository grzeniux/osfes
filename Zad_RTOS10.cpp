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
Odp:
T = 4000

1. Mamy takie same priorytety, więc zadania wykonują sie równoległe
2. Startujemy z Thread1 ustala czas T=0 i czekamy aż do T=1000
3. T=0, Thread2 startuje bierze mutex i ma go aż do T=3000
4. T=1000, próba wzięcia mutexa przez Thread1 - nieudana bo Thread2, czeka max do T=6000
5. T=3000, Thread2 oddaje mutex i usuwa się, a Thread1 bierze go i czeka az do T=4000
6. Thread1 oddaje mutex printuje T=4000 i usuwa się
