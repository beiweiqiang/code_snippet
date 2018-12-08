#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;

void *child(void *arg) {
    printf("child\n");
    // use semaphore here
    sleep(1);
    sem_post(&s);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    sem_init(&s, 0, 0);
    // init semaphore here
    pthread_create(&p, NULL, child, NULL);
    sem_wait(&s);
    // use semaphore here
    printf("parent: end\n");
    return 0;
}
