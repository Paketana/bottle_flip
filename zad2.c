/*
Za pomocą kolejki komunikatów stwórz komunikację 
między dwoma procesami (w obrębie jednego pliku/dwóch programów). 
Jeden proces powinien naprzemiennie przesyłać „zalicz”, „kolos”. 
Drugi powinien te treści odbierać.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msgbuf {
    long mtype;
    char mtext[128];
} message_buf;

void sender(int msqid) {
    message_buf sbuf;
    sbuf.mtype = 1;
    char *messages[] = {"zalicz", "kolos"};
    int msg_index = 0;

    while (1) {
        strcpy(sbuf.mtext, messages[msg_index]);
        msg_index = (msg_index + 1) % 2;

        if (msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, 0) < 0) {
            perror("msgsend");
            exit(1);
        }
        sleep(1);
    }
}

void receiver(int msqid) {
    message_buf rbuf;

    while (1) {
        if (msgrcv(msqid, &rbuf, 128, 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        printf("Received: %s\n", rbuf.mtext);
    }
}

int main() {
    int msqid;
    key_t key = 1234;

    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    if (fork() == 0) {
        sender(msqid);
    }
    else {
        receiver(msqid);
    }

    return 0;
}