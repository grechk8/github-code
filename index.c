#include <assert.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static struct dim {
    int32_t m;
    int32_t n;
} global;

void *thread1(void* _) {
    assert(_ == NULL);
    global.m += 2;
    global.n += 2;
    printf("[thread1]:\tlocal  { m: %d, n: %d }\n", global.m, global.n);
    return NULL;
}

void *thread2(void* args) {
    assert(args != NULL);
    global.m += 3;
    global.n += 3;
    printf("[thread2]:\tlocal  { m: %d, n: %d }\n", global.m, global.n);
    return NULL;
}

int32_t main(int32_t argc, char* argv[]) {
    int32_t m = 10;
    int32_t n = 1;
    if (argc > 1) {
        m = atoi(argv[1]);
    }
    if (argc > 2) {
        n = atoi(argv[2]);
    }

    global.m = m;
    global.n = n;
    printf("[main]:\t\tglobal { m: %d, n: %d }\n", global.m, global.n);

    pthread_t tid1;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_join(tid1, NULL);
    printf("[main]:\t\tglobal { m: %d, n: %d }\n", global.m, global.n);

    pthread_t tid2;
    pthread_create(&tid2, NULL, thread2, &global);
    pthread_join(tid2, NULL);
    printf("[main]:\t\tglobal { m: %d, n: %d }\n", global.m, global.n);

    return 0;
}
