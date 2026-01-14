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

// 1.  T=0: Semafor zostaje utworzony jako otwarty (wartość 1). `Thread2` usypia na 1000 ms.
// 2.  T=0: `Thread1` próbuje zająć semafor funkcją `osSemaphoreAcquire` z czasem oczekiwania 0.
// 3.  T=0: Ponieważ semafor jest wolny, `Thread1` zajmuje go natychmiast (funkcja zwraca sukces `osOK`), wypisuje "OK, " i przerywa pętlę.
// 4.  T=0: Nie wystąpiło żadne opóźnienie w `Thread1`, więc różnica czasu wynosi 0. Wynik to `T = 0`.
