// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t mux;

void Thread2(void* param) {
    vTaskDelay(100);
    if (pdTRUE == xSemaphoreTake(mux, 800)) {
        vTaskDelay(1500);
        xSemaphoreGive(mux);
    }
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    TickType_t t = xTaskGetTickCount();
    vTaskDelay(200);
    if (pdTRUE == xSemaphoreTake(mux, 500)) {
        vTaskDelay(100);
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


1. Thread2 startuje jako pierwszy bo ma wyższy priorytet
2. Thread2 Wpada w vTaskDelay(100) wiec oddaje prace Thread1 - 
3. Startuje Thread1 - ustala aktualny czas czyli T=0
4. Thread1 Wpada w vTaskDelay(200) wiec oddaje prace do Thread2
5. T=100 budzi się Thread2 (wyzszy priorytet) bierze mutexa, trzyma go az do T=1600 i oddaje go i usuwa się
6. W T=200 Thread 1 próbuje zajac mutex ale jest zajety wiec wraca do stanu blocked
7. Maksymalny czas oczekiwania na mutex do 500, wiec Thread1 podda sie w chwili T=700
T=700

