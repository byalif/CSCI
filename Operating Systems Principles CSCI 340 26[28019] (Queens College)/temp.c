#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
// #include <mqueue.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <sys/stat.h>

#define SIZ 128
#define MQ_NAME "/mq_cola_queue"
const int MSG_SIZE = 128;
const int MSG_CAPACITY = 50;

typedef struct
{
    char msg[80];
    int NEWLINE_COUNT;
    int WORD_COUNT;
    int CHAR_COUNT;
    int MAX_LINE;

} Message;

int newMain(char *input)
{

    // struct mq_attr attributes = {
    //     .mq_flags = 0,
    //     .mq_maxmsg = 10,
    //     .mq_curmsgs = 0,
    //     .mq_msgsize = sizeof(Message)

    // };
    // mqd_t queue = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0644, &attributes);

    int fd[2];
    if (pipe(fd) < 0)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    int id = fork();
    int f1;
    int i = 0;

    if (id == 0)
    {
        close(fd[0]);
        if ((f1 = open(input, O_RDONLY, 0)) == -1)
        {
            printf("Can't open %s \n", input);
            return 2;
        }
        int n;
        char buf[SIZ];
        while ((n = read(f1, buf, SIZ)) > 0)
            write(fd[1], buf, n);
        close(fd[1]);
        close(f1);
        printf("Child: file %s sent to pipe \n", input);
    }
    else
    {
        close(fd[1]);
        char line[128];
        int count = 0;
        int newLine = 1;
        int n = read(fd[0], line, SIZ);
        int max = 0;
        int curL = 0;
        for (int i = 0; i < 128; i++)
        {
            if (line[i] == '\0')
                break;

            curL++;
            if (line[i] == '\n')
            {
                newLine++;
                if (curL > max)
                {
                    max = curL - 1;
                }
                curL = 0;
            }
            count++;
        }

        if (newLine == 1)
            max = count;

        // struct timespec timeout = {0, 0};

        // Message msg;
        // msg.CHAR_COUNT = count;
        // msg.MAX_LINE = max;
        // msg.NEWLINE_COUNT = newLine;
        // strcpy(msg.msg, line);
        // if (mq_timedsend(queue, (char *)&msg, sizeof(Message), 1, &timeout) == -1)
        // {
        //     printf("Parent: mq_send error\n");
        //     return 4;
        // }

        // write(STDOUT_FILENO, "Parent: msg 1 sent\n", 19);

        // mq_close(queue);
        // mq_unlink(MQ_NAME);

        // wait(NULL);
        // write(STDOUT_FILENO, "Parent: Done...\n", 16);
        printf("Parent: recieved.\nCharacters: %d \nMax line length: %d \nnewLines: %d\nMsg: %s\n\n", count, max, newLine, line);
        close(fd[0]);
        return EXIT_SUCCESS;
    }

    // if (id == 0)
    // {
    //     Message msg;
    //     unsigned int prio;
    //     struct timespec timeout = {0, 0};

    //     // Get the first message.
    //     size_t numRead = mq_timedreceive(queue, (char *)&msg, sizeof(msg), &prio, &timeout);

    //     // if (numRead == -1)
    //     // {
    //     //     printf("Child: mq_read error");
    //     //     return 5;
    //     // }

    //     write(STDOUT_FILENO, "Child: Message 1 content is \n***", 33);
    //     write(STDOUT_FILENO, msg.msg, (size_t)numRead);
    //     write(STDOUT_FILENO, "***\n", 4);

    //     mq_close(queue);
    //     mq_unlink(MQ_NAME);

    //     return EXIT_SUCCESS;
    // }
    return 0;
}

int main(int argc, char *argv[])
{

    int BUFFER_SIZE = 0;
    char *OPTIONS;
    // default input file placeholder
    char INPUT_FILE[13] = "myinpfile.txt";
    // Array of input files
    char **INPUT_FILES;
    // size of input file list
    int files = 0;

    if (argc < 2)
    {
        printf("You need to add buffer size");
        return 1;
    }

    char *p;
    int num;

    if (argv[1][0] != '-')
    {
        BUFFER_SIZE = strtol(argv[1], &p, 10);
        strcpy(OPTIONS, "-ncb");
    }
    else
    {
        // This will return because you NEED buffer size
        if (argc < 3)
        {
            printf("You need to add buffer size");
            return 3;
        }
        BUFFER_SIZE = strtol(argv[2], &p, 10);
        strcpy(OPTIONS, argv[1]);
    }

    // If this is the case then we can disgard "myinpfile.txt"
    if (argc > 2)
    {
        int start;
        // if you didn't specify OPTIONS command line arg, the start will be index 2
        if (argv[1][0] != '-')
            start = 2;
        else
            start = 3;

        // lets store how many input files there are
        files = argc - start;
        // create 2d array for each input argument by allocating dynamic memory
        INPUT_FILES = (char **)malloc(files * sizeof(char *));
        for (int i = start; i < argc; i++)
        {
            // create 1d array for each character in string
            INPUT_FILES[i - start] = (char *)malloc(100 * sizeof(char));
            strcpy(INPUT_FILES[i - start], argv[i]);
        }
    }

    for (int i = 0; i < files; i++)
    {

        newMain(INPUT_FILES[i]);
    }

    // newMain("gg.txt");``

    for (int i = 0; i < files; i++)
    {
        // create 1d array for each character in string
        free(INPUT_FILES[i]);
    }

    free(INPUT_FILES);

    return 0;
}
