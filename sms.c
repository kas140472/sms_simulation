#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#define NUM_MESSAGES 1000
#define MESSAGE_LENGTH 100
#define NUM_SENDERS 5
#define MEAN_SEND_TIME 2.0
#define FAILURE_RATE 0.1
#define PROGRESS_UPDATE_INTERVAL 5

int messages_sent = 0;
int messages_failed = 0;
double total_send_time = 0.0;

pthread_mutex_t progress_lock = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    int i;
    for (i = 0; i < NUM_MESSAGES; i++) {
        
        char phone_number[12];
        sprintf(phone_number, "%010d", rand() % 10000000000);

        char message[MESSAGE_LENGTH];
        int j;
        for (j = 0; j < MESSAGE_LENGTH - 1; j++) {
            message[j] = 'A' + rand() % 26;
        }
        message[MESSAGE_LENGTH - 1] = '\0';

       
        /*double send_time = -MEAN_SEND_TIME * log((double)rand() / RAND_MAX);
        usleep((useconds_t)(send_time * 1e6));

        
        if ((double)rand() / RAND_MAX < FAILURE_RATE) {
            pthread_mutex_lock(&progress_lock);
            messages_failed++;
            pthread_mutex_unlock(&progress_lock);
        } else {
            pthread_mutex_lock(&progress_lock);
            messages_sent++;
            total_send_time += send_time;
            pthread_mutex_unlock(&progress_lock);
        }*/
    }
    return NULL;
}

void *sender(void *arg) {
    double mean_send_time = *(double *)arg;
    double error_rate = *((double *)arg + 1);

    while (1) {
        
        double send_time = -mean_send_time * log((double)rand() / RAND_MAX);
        usleep((useconds_t)(send_time * 1e6));

        
        if ((double)rand() / RAND_MAX < error_rate) {
            pthread_mutex_lock(&progress_lock);
            messages_failed++;
            pthread_mutex_unlock(&progress_lock);
        } else {
            pthread_mutex_lock(&progress_lock);
            messages_sent++;
            total_send_time += send_time;
            pthread_mutex_unlock(&progress_lock);
        }
    }
    return NULL;
}

void *progress_monitor(void *arg) {
    while (1) {
        sleep(PROGRESS_UPDATE_INTERVAL);
        pthread_mutex_lock(&progress_lock);
        printf("Messages Sent: %d\n", messages_sent);
        printf("Messages Failed: %d\n", messages_failed);
        if (messages_sent > 0) {
            double average_time_per_message = total_send_time / messages_sent;
            printf("Average Time per Message (seconds): %.2f\n", average_time_per_message);
        }
        pthread_mutex_unlock(&progress_lock);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    pthread_t producer_thread, progress_thread;

    //pthread_create(&progress_thread, NULL, progress_monitor, NULL);

    int num_senders = NUM_SENDERS;
    printf("Enter the number of sender threads: ");
    scanf("%d", &num_senders);
    double sender_args[num_senders][2];
    pthread_t sender_threads[num_senders];

    for (int i = 0; i < num_senders; i++) {
        printf("Enter the mean processing time for sender %d: ", i + 1);
        scanf("%lf", &sender_args[i][0]);
        printf("Enter the error rate for sender %d: ", i + 1);
        scanf("%lf", &sender_args[i][1]);
    }

    for (int i = 0; i < num_senders; i++) {
        pthread_create(&sender_threads[i], NULL, sender, (void *)sender_args[i]);
    }

    pthread_create(&progress_thread, NULL, progress_monitor, NULL);

    pthread_join(progress_thread, NULL);

    for (int i = 0; i < NUM_SENDERS; i++) {
        pthread_cancel(sender_threads[i]);
    }

    return 0;
}
