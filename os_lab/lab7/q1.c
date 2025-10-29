#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_KEY 1234

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int isPalindrome(char *str) {
    int i = 0, j = strlen(str) - 1;
    while (i < j) if (str[i++] != str[j--]) return 0;
    return 1;
}

void sender() {
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    printf("Enter number: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);
    message.msg_text[strcspn(message.msg_text, "\n")] = 0;
    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    printf("Number sent.\n");
}

void receiver() {
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
    printf("Received number: %s\n", message.msg_text);
    printf("%s palindrome.\n", isPalindrome(message.msg_text) ? "Is" : "Not");
    msgctl(msgid, IPC_RMID, NULL);
}

int main() {
    if (fork() == 0) {
        sleep(1);
        receiver();
    } else {
        sender();
    }
    return 0;
}

