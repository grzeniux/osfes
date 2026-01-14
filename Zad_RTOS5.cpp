// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

SemaphoreHandle_t sem;

void Thread2(void* param) {
    vTaskDelay(1000);
    xSemaphoreGive(sem);
    vTaskDelete(NULL);
}

void Thread1(void* param) {
    static volatile int i;
    TickType_t t = xTaskGetTickCount();
    for (i = 0; i < 3000; i++) {
        if (pdTRUE == xSemaphoreTake(sem, 0)) {
            printf("OK,");
            i = 3000;
        } else {
            vTaskDelay(1);
        }
    }
    printf("T = %d", xTaskGetTickCount() - t);
    vTaskDelete(NULL);
}

int main(void) {
    sem = xSemaphoreCreateBinary();
    xTaskCreate(Thread1, "thread1", 512, NULL, 4, NULL);
    xTaskCreate(Thread2, "thread2", 512, NULL, 2, NULL);
    vTaskStartScheduler();
}

Odp:
T=1001

1. Thread1 ma większy priorytet, więc startuje i ustala czas T=0
2. Thread1 wykonuje xSemaphoreTake(sem, 0). Ponieważ semafor jest pusty, funkcja zwraca błąd (nie blokuje, bo czas oczekiwania to 0).
   Thread1 wchodzi do bloku else i wykonuje vTaskDelay(1).
   Thread1 przechodzi w stan BLOCKED na 1 tik.
3. Ponieważ Thread1 jest zablokowany, procesor otrzymuje Thread2.
   Thread2 wykonuje vTaskDelay(1000).
   Thread2 przechodzi w stan BLOCKED na 1000 tików.
4. T = 1 do T = 999:
   W chwili T=1 budzi się Thread1. Thread2 wciąż śpi.
   Thread1 sprawdza semafor -> Pusty.
   Thread1 wykonuje vTaskDelay(1) -> Zasypia do T=2.
   Ten cykl powtarza się aż do T=1000. Zmienna i w pętli inkrementuje się co 1 tik.
5. T = 1000 (Moment krytyczny):
   W tym samym tiku budzą się oba zadania:
   Thread2 kończy vTaskDelay(1000).
   Thread1 kończy swoje vTaskDelay(1) z poprzedniego cyklu (T=999).
   Oba zadania są w stanie READY.
   Scheduler musi wybrać, kogo uruchomić. Wybiera Thread1, ponieważ ma wyższy priorytet (4).
   Thread1 sprawdza xSemaphoreTake. Semafor jest nadal pusty! (Thread2 się obudził, ale nie dostał jeszcze czasu procesora, żeby oddać semafor).
   Thread1 ponownie wykonuje vTaskDelay(1) i zasypia do T=1001.
6. T = 1000 (ciąg dalszy):
   Teraz, gdy Thread1 śpi, procesor przejmuje Thread2.
   Thread2 wykonuje xSemaphoreGive(sem). Semafor staje się pełny.
   Thread2 kończy działanie (vTaskDelete).
7. T = 1001:
   Thread1 budzi się z uśpienia.
   Thread1 wykonuje xSemaphoreTake(sem, 0).
   Tym razem sukces (pdTRUE), ponieważ w poprzednim kroku Thread2 oddał semafor.
   Program wypisuje "OK,".
   Pętla zostaje przerwana (i = 3000).
   Program oblicza czas: xTaskGetTickCount() - t.
   Aktualny czas to 1001, czas startu to 0.
   
Wynik: 1001 - 0 = 1001.


za duzo xd
