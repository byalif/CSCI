#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>

#define MQ_NAME "/mq_cola_queue"
const int MSG_SIZE = 128;
const int MSG_CAPACITY = 50;

typedef struct
{
    char msg[18];
    int ati;
    char dude[10];
} Message;

int main(int argc, char *argv[])
{

    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(Message)

    };
    mqd_t queue = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0644, &attributes);

    // parent process (server)

    int id = fork();
    if (id == 0)
    {
        // char msg[80];
        Message msg;
        unsigned int prio;
        struct timespec timeout = {0, 0};

        // Get the first message.
        size_t numRead = mq_timedreceive(queue, (char *)&msg, sizeof(msg), &prio, &timeout);

        // if (numRead == -1)
        // {
        //     printf("Child: mq_read error");
        //     return 5;
        // }

        write(STDOUT_FILENO, "Child: Message 1 content is \n***", 33);
        write(STDOUT_FILENO, msg.dude, sizeof(msg.dude));
        write(STDOUT_FILENO, "\n", 2);
        write(STDOUT_FILENO, "Child: Message 2 content is \n***", 33);
        write(STDOUT_FILENO, msg.msg, sizeof(msg.msg));
        write(STDOUT_FILENO, "***\n", 4);

        mq_close(queue);
        mq_unlink(MQ_NAME);

        return EXIT_SUCCESS;

        // child process (client)
    }
    else
    {

        struct timespec timeout = {0, 0};

        Message msg;
        strcpy(msg.dude, "ummm okay");
        strcpy(msg.msg, "your annoying asf");
        if (mq_timedsend(queue, (char *)&msg, sizeof(Message), 1, &timeout) == -1)
        {
            printf("Parent: mq_send error\n");
            return 4;
        }

        write(STDOUT_FILENO, "Parent: msg 1 sent\n", 19);

        mq_close(queue);
        mq_unlink(MQ_NAME);

        wait(NULL);
        write(STDOUT_FILENO, "Parent: Done...\n", 16);
        return EXIT_SUCCESS;
    }

    return 0;
}