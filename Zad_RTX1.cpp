// Korzystając z systemu RTX uruchomiono poniższy program. 
// Podaj jaki tekst program wypisze na standardowe wyjście i 
// wyjaśnij dlaczego taki, opisując przebieg wykonywania programu.

osSemaphoreId_t sem;

void Thread2(void* param) {
    osDelay(1000);
    osSemaphoreRelease(sem);
    osDelay(NULL);
}

void Thread1(void* param) {
    uint32_t t = osKernelGetTickCount();
    for (volatile int i = 0; i < 2000; i++) {
        if (osOK == osSemaphoreAcquire(sem, 0)) {
            printf("OK, ");
            break;
        }
        osDelay(1);
    }
    printf("T = %d", osKernelGetTickCount() - t);
    osThreadExit();
}

int main(void) {
    osKernelInitialize();
    sem = osSemaphoreNew(1, 1, NULL);
    osThreadNew(Thread1, NULL, NULL);
    osThreadNew(Thread2, NULL, NULL);
    osKernelStart();
}

1. Start (main):
    Semafor zostaje utworzony: osSemaphoreNew(1, 1, NULL). 
    Oznacza to: wartość maksymalna 1, wartość początkowa 1. Semafor jest "otwarty" (dostępny).
    Uruchamiane są wątki Thread1 i Thread2.

2. Thread2 (T = 0):
    Wykonuje osDelay(1000), czyli idzie spać na 1000 jednostek czasu (ticków).

3. Thread1 (T = 0):
    Pobiera aktualny czas: t = 0.
    Wchodzi do pętli for.
    Wykonuje osSemaphoreAcquire(sem, 0). 
    Ponieważ semafor przy starcie miał wartość 1, wątek zajmuje go 
    natychmiast (zdejmuje 1 z licznika, licznik wynosi teraz 0).
    Warunek if (osOK == ...) jest spełniony.
    Program wypisuje: OK, .
    break przerywa pętlę i wątek przechodzi do wypisania czasu.
