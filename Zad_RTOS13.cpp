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
Odp:
T = 2000

1. Thread1 zaczyna i ustala czas T=0, następnie czeka przechodzi w stan blocked aż do T=1000
2. T=0 Startuje Thread2 i przechodzi w stan blocked aż do T=3000
3. T=1000, próba wzięcia mutexa przez Thread1, nieudana ponieważ jest pusty mutex
4. T=2000, mija czas oczekiwania Thread1
5. Funkcja xSemaphoreTake konczy sie pdFALSE ale odblokowuje Thread1 bo koniec czasu oczekiwania
    Thread1 robi printf T=2000
    Thread1 usuwa się
5. T=3000, Thread2 oddaje semafor - ale Thread1 juz nie istnieje
6. Thread2 usuwa się




