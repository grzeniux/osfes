// Korzystając z systemu FreeRTOS uruchomiono poniższy program. 
// Podaj jaką wartość T program wypisze na standardowe wyjście i wyjaśnij dlaczego taką, 
// opisując przebieg wykonywania programu.

static volatile int run = 1;

void Thread(void* param){
    volatile int counter = 0;
    while (run) {
        counter++;
        if (counter == 1000) {
            run = 0;
        }
        vTaskDelay(1);
    }
    printf("counter = %d\n", counter);
    vTaskDelete(NULL);
}

int main(void) {
    xTaskCreate(Thread, "thread1", 512, NULL, 2, NULL);
    xTaskCreate(Thread, "thread2", 512, NULL, 4, NULL);
    vTaskStartScheduler();
}
Odp:
counter = 999
counter = 1000

1. Thread2 startuje jako pierwszy bo ma wyższy prioryter
2. Thread2 zwieksza swój counter na 1 i wpada w vTaskDelay(1)
3. W tym czasie Thread1 sie ząłącza i zwiększa counter na 2
4. Thread2 jako pierwszy doliczy do 1000 i ustawi flage run=0 i wpada w vTaskDelay(1)
5. Thread1 nie wejdzie juz do pętli bo widzi, że run=0 i zrobi printf("counter=999") poczym sie usunie
6. Thread2 dokonczy swoje zadanie i wypisze counter=1000

