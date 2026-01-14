// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t sem;

void Thread2(void* param) {
    vTaskDelay(2000);
    xSemaphoreGive(sem);
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    static volatile int i;
    TickType_t t = xTaskGetTickCount();
    for (i = 0; i < 1000; i++) {
        if (pdTRUE == xSemaphoreTake(sem, 0)) {
            printf("OK,");
            i = 1000;
        } else {
            vTaskDelay(1);
        }
    }
    printf("T = %d", xTaskGetTickCount() - t);
    vTaskDelete(NULL);
}

int main(void) {
    sem = xSemaphoreCreateBinary();
    xTaskCreate(Thread1, "thread1", 512, NULL, 3, NULL);
    xTaskCreate(Thread2, "thread2", 512, NULL, 3, NULL);
    vTaskStartScheduler();
}
Odp:
T = 1

1. Tworzymy pusty SemaforBinarny
2. Thready maja ten sam prioryter wiec beda pracowac na przemian
3. Thread1 zaczyna i ustawia T=0 rusza z pętlą i próbuje wziąc mutex ale sie mu nie udaje bo jest pusty
    więc robi vTaskDelay(1) i oddaje procesor
4. Zaczyna Thread2 i przechodzi w blocked aż do T=2000
5. T=1, Thread1 przechodzi całą pętle aż do T=1000
    Thread1 printuje T=1000 i usuwa się
6. T=2000, Thread2 oddaje semafor ale to juz bez znaczenia bo Thread1 sie usunął, Thread2 usuwa się

