#include <nuttx/config.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

// Global variable for the counter
volatile int counter = 0;
volatile int running = 1;

// Mutex to protect access to counter
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to print timestamp
void print_timestamp(const char* task_name)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    double time_in_seconds = ts.tv_sec + ts.tv_nsec / 1e9;
    printf("[DEBUG] %.2f %s - izvrÅ¡avanje\n", 
    time_in_seconds, task_name);
}

// Signal handler to stop the program
void handle_sigint(int sig)
{
    printf("Caught signal %d, stopping...\n", sig);
    running = 0;
}

// Task 1: Increment the counter every 3 seconds
void* task1_func(void* arg)
{
    while (running)
    {
        print_timestamp("Task 1");

        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);

        sleep(3);
    }
    return NULL;
}

// Task 2: Print the value of the counter every 7 seconds
void* task2_func(void* arg)
{
    while (running)
    {
        print_timestamp("Task 2");

        pthread_mutex_lock(&counter_mutex);
        printf("Counter value: %d\n", counter);
        pthread_mutex_unlock(&counter_mutex);

        sleep(7);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t task1;
    pthread_t task2;
    int ret;

    // Register signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, handle_sigint);

    // Create Task 1
    ret = pthread_create(&task1, NULL, task1_func, NULL);
    if (ret != 0)
    {
        printf("Failed to create Task 1: %d\n", ret);
        return -1;
    }

    // Create Task 2
    ret = pthread_create(&task2, NULL, task2_func, NULL);
    if (ret != 0)
    {
        printf("Failed to create Task 2: %d\n", ret);
        return -1;
    }

    // Wait for tasks to finish
    pthread_join(task1, NULL);
    pthread_join(task2, NULL);

    printf("Custom counter app stopped.\n");

    return 0;
}