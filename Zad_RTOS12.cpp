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
Odp:
T= 600

1. Tworzony jest pusty semafor
    Thread1 startuje pierwszy (wyższy priorytet).
    Pobiera czas t=0.
        idzie spać do T=200.
    Thread2 (Priorytet 3) dostaje procesor.
        idzie spać do T=600.
2. T=200,
    Thread1 budzi się.
    Próbuje wykonać xSemaphoreTake(sem, 400).
    Ponieważ semafor jest pusty (nikt go nie oddał), Thread1 nie może go wziąć.
    Thread1 wchodzi w stan Blocked (czekania) na maksymalnie 400 ticków.
    Oczekiwany czas wybudzenia (timeout): T = 200 + 400 = 600.
3. T=600
    Mija czas uśpienia Thread2 (kończy się vTaskDelay(600)).
    Mija czas oczekiwania Thread1 na semafor (kończy się timeout 400 ticków).
    Oba zadania stają się gotowe (Ready).
    Scheduler wybiera Thread1 
4. Dalsze działanie w T=600:
    Thread1 wznawia działanie w wyniku timeoutu. Funkcja xSemaphoreTake zwraca pdFALSE (nie udało się wziąć semafora, ale czas minął).
    Thread1 wykonuje printf T=600
    Thread1 usuwa się.
5. Po T=600:
    Dopiero teraz Thread2 dostaje procesor.
    Wykonuje xSemaphoreGive(sem), ale nikt już na to nie czeka.
    Thread2 usuwa się.