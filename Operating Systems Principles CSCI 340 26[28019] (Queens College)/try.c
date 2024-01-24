#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <sys/stat.h>

#define MQ_NAME "/Queue"
const int MSG_SIZE = 128;
const int MSG_CAPACITY = 50;
int nLine = 0;
int maxL = 0;
int chars = 0;
int words = 0;

// This struct helps us store msg contents in an Object
typedef struct
{
    char msg[40];
    char newLine[128];
    char words[128];
    char maxLine[128];
    char character[128];

} Message;

void checkOptions(char *str)
{
    for (int i = 0; i < str[i] != '\0'; i++)
    {
        if (str[i] == 'n')
            nLine = 1;
        else if (str[i] == 'c')
            words = 1;
        else if (str[i] == 'b')
            chars = 1;
        else if (str[i] == 'm')
            maxL = 1;
    }
}

int main(int argc, char *argv[])
{

    // Defined attributes for the msg queue
    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(Message)

    };
    mqd_t queue = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0644, &attributes);

    if (queue == (mqd_t)-1)
    {
        printf("mq_open error");
        mq_unlink(MQ_NAME);
        return 2;
    }

    // default Buffer size
    int BUFFER_SIZE = 128;
    // default OPTIONS placeholder
    char OPTIONS[6] = "-ncb\0";
    // default input placeholder
    char INPUT_FILE[13] = "myinpfile.txt";
    // Array of input files
    char **INPUT_FILES;
    // size of input file list
    int files = 0;

    if (argc < 2)
    {
        printf("You need to add buffer size");
        return 3;
    }

    if (argv[1][0] != '-')
    {
        BUFFER_SIZE = (int)strtol(argv[1], (char **)NULL, 10);
        checkOptions(OPTIONS);
    }
    else
    {
        // This will return because you NEED buffer size
        if (argc < 3)
        {
            printf("You need to add buffer size");
            return 3;
        }

        BUFFER_SIZE = (int)strtol(argv[2], (char **)NULL, 10);
        strcpy(OPTIONS, argv[1]);
        checkOptions(argv[1]);
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

    int fd[2];
    if (pipe(fd) < 0)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    int id = fork();

    if (id < 0)
    {
        fprintf(stderr, "fork failed");
    }
    else if (id == 0)
    {
        close(fd[0]);

        for (int i = 0; i < files; i++)
        {
            int f1;
            int len = 0;
            int j = 0;
            while (INPUT_FILES[i][j] != '\0')
            {
                j++;
                len++;
            }
            len++;
            if ((f1 = open(INPUT_FILES[i], O_RDONLY, 0)) == -1)
            {
                printf("Can't open %s \n", INPUT_FILES[i]);
                return 2;
            }
            int n;
            int count = 0;
            char buf[1028];
            write(fd[1], &len, sizeof(int));
            write(fd[1], INPUT_FILES[i], len);
            while ((n = read(f1, buf, BUFFER_SIZE)) > 0)
            {
                write(fd[1], &n, sizeof(int));
                write(fd[1], buf, n);
                count++;
                // Writing data to the pipe for the parent to send to the Possix msg QUEUE
            }
            // int sz = 0;
            // int k = 0;
            // while (buf[k++] != '\0')
            // {
            //     sz++;
            // }
            // sz++;

            // printf("%s\n", buf);
            close(f1);
        }
        close(fd[1]);
        unsigned int prio;
        struct timespec timeout = {0, 0};

        for (int i = 0; i < files; i++)
        {
            Message msg;
            size_t numRead = mq_timedreceive(queue, (char *)&msg, sizeof(Message), &prio, NULL);
            if (numRead == -1)
            {
                printf("Parent: mq_read error\n");
                return 4;
            }

            int i = 0;
            int len1 = 0;
            int len2 = 0;
            int len3 = 0;
            int len4 = 0;
            // Counting the length of each output from the message queue
            while (msg.newLine[i++] != '\0')
                len1++;
            i = 0;
            while (msg.words[i++] != '\0')
                len2++;
            i = 0;
            while (msg.character[i++] != '\0')
                len3++;
            i = 0;
            while (msg.maxLine[i++] != '\0')
                len4++;

            // Final message to the STDOUT
            // printf("%s", msg.msg)
            if (nLine == 1)
                write(STDOUT_FILENO, msg.newLine, len1);
            if (words == 1)
                write(STDOUT_FILENO, msg.words, len2);
            if (chars == 1)
                write(STDOUT_FILENO, msg.character, len3);
            if (maxL == 1)
                write(STDOUT_FILENO, msg.maxLine, len4);
            write(STDOUT_FILENO, "\n", 1);
        };
        mq_close(queue);
        mq_unlink(MQ_NAME);
        // Terminate child process
        write(STDOUT_FILENO, "Child: Terminating.\n", 20);
    }
    else
    {
        close(fd[1]);
        for (int i = 0; i < files; i++)
        {
            char line[2028];
            int count = 0;
            int newLine = 0;
            int len;
            char file[50];
            int lenofFile;

            // Reading contents of the pipe
            read(fd[0], &lenofFile, sizeof(int)); // sz of input string
            read(fd[0], file, lenofFile);         // input string
            read(fd[0], &len, sizeof(int));       // sz of file contents
            read(fd[0], line, len);               // file contents
            int max = 0;
            int words = 0;
            int curL = 0;
            for (int i = 0; line[i] != '\0'; i++)
            {
                if (line[i] == ' ')
                {
                    words++;
                }
                else if (line[i] == '\n')
                {
                    if (curL > max)
                    {
                        // setting new max line character
                        max = curL;
                    }
                    curL = 0;
                    newLine++;
                    words++; // since with every next line new words start. corner case 1
                }
                else if (line[i] != '\n')
                {
                    curL++;
                    count++;
                }
            }

            // if theres only one line, max new lines is equal to characters..
            if (newLine == 1)
            {
                max = len;
            }

            struct timespec timeout = {0, 0};

            Message msg;
            strcpy(msg.msg, line);
            snprintf(msg.newLine, 128, "%s:\t newline count is:\t %d \n", file, newLine);
            snprintf(msg.character, 128, "%s:\t character count is:\t %d \n", file, len);
            snprintf(msg.maxLine, 128, "%s:\t maximum line length is:\t %d \n", file, max);
            snprintf(msg.words, 128, "%s:\t word count is:\t %d \n", file, words);

            if (mq_timedsend(queue, (char *)&msg, sizeof(Message), 1, NULL) == -1)
            {
                printf("Parent: mq_send error %d\n", errno);
                return 4;
            }
        }
        close(fd[0]);
        mq_close(queue);
        mq_unlink(MQ_NAME);
        wait(NULL);
        for (int i = 0; i < files; i++)
        {
            // free all the memory for each character in string
            free(INPUT_FILES[i]);
        }

        free(INPUT_FILES);
        write(STDOUT_FILENO, "Parent: Terminating.\n", 21);
    }

    return 0;
}
