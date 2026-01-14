# Analiza zadania z semaforami w systemie RTX

## 1. Treść polecenia
Korzystając z systemu RTX uruchomiono poniższy program. Podaj jaki tekst program wypisze na standardowe wyjście i wyjaśnij dlaczego taki, opisując przebieg wykonywania programu.

---

## 2. Oryginalny kod programu

```c
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
```

---

## 3. Kod z wyjaśnieniami i komentarzami

Poniżej znajduje się kod z komentarzami wyjaśniającymi krok po kroku, co dzieje się w czasie wirtualnym systemu (T).

```c
osSemaphoreId_t sem;

void Thread2(void* param) {
    // T=0: Thread2 startuje (lub scheduler go wybiera).
    // Wywołuje opóźnienie 1000 ticków. Wątek wchodzi w stan BLOCKED.
    // Procesor zostaje przekazany do Thread1.
    osDelay(1000);
    
    // Ta linia (Release) wykonałaby się w T=1000.
    // Jednak Thread1 zakończy działanie programu dużo wcześniej (w T=0).
    osSemaphoreRelease(sem);
    
    osDelay(NULL);
}

void Thread1(void* param) {
    // T=0: Thread1 otrzymuje sterowanie, ponieważ Thread2 śpi.
    uint32_t t = osKernelGetTickCount(); // t = 0
    
    for (volatile int i = 0; i < 2000; i++) {
        // T=0: Próba zajęcia semafora (Acquire) z timeoutem 0.
        // Timeout 0 oznacza "spróbuj i wróć natychmiast".
        // W main() semafor utworzono z wartością 1 (osSemaphoreNew(1, 1...)).
        // Zatem semafor JEST DOSTĘPNY. Funkcja zwraca osOK.
        if (osOK == osSemaphoreAcquire(sem, 0)) {
            
            // Wchodzimy do środka w pierwszej iteracji.
            printf("OK, ");
            
            // Break wyrzuca nas z pętli for.
            break;
        }
        // Ta instrukcja delay(1) się NIE wykona, bo if (osOK) był prawdą.
        osDelay(1);
    }
    
    // T=0: Jesteśmy po pętli.
    // Czas trwania = obecny czas (0) - czas startu (0) = 0.
    printf("T = %d", osKernelGetTickCount() - t);
    
    // Wątek kończy pracę.
    osThreadExit();
}

int main(void) {
    osKernelInitialize();
    
    // UTWORZENIE SEMAFORA
    // Argumenty: max_count=1, initial_count=1.
    // initial_count=1 oznacza, że semafor na starcie jest "zielony" (wolny).
    sem = osSemaphoreNew(1, 1, NULL);
    
    osThreadNew(Thread1, NULL, NULL);
    osThreadNew(Thread2, NULL, NULL);
    
    osKernelStart();
}
```

---

## 4. Krótka odpowiedź na kolokwium

**Wynik:**
```text
OK, T = 0
```

**Uzasadnienie:**
1.  **T=0:** Semafor zostaje utworzony jako otwarty (wartość 1). `Thread2` usypia na 1000 ms.
2.  **T=0:** `Thread1` próbuje zająć semafor funkcją `osSemaphoreAcquire` z czasem oczekiwania 0.
3.  **T=0:** Ponieważ semafor jest wolny, `Thread1` zajmuje go natychmiast (funkcja zwraca sukces `osOK`), wypisuje "OK, " i przerywa pętlę (`break`).
4.  **T=0:** Nie wystąpiło żadne opóźnienie w `Thread1`, więc różnica czasu wynosi 0. Wynik to `T = 0`.