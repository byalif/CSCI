// Alif Rahi 23792468

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// This library to get the os version/release
#include <sys/utsname.h>

// for the possix message queue
#include <mqueue.h>
#include <fcntl.h>

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
    char newLine[128 * 10];
    char words[128];
    char maxLine[128];
    char character[128];

} Message;

// This method enables the outputs you specify in the OPTIONS args
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

    struct utsname details;

    int ret = uname(&details);

    // Defined attributes for the msg queue
    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(Message)

    };
    // Possix message queue opens my queue
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
    char *INPUT_FILE = "Project1Input.txt";

    // These if statements are error checking to see if the args are valid
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
        // These several below contain messages I will STDOUT
        char pidmsg[128];
        char ppidmsg[128];
        char direct[128];
        char hName[128];
        char hostname[1024];

        hostname[1023] = '\0';
        // This method stores the host name into "hostname"
        gethostname(hostname, 1023);

        // Snprintf is to copy and string into a char array
        // Parent process is the getppid()
        snprintf(ppidmsg, 128, "Parent process ID is:\t %d \n", getppid());
        // child process is the getpid()
        snprintf(pidmsg, 128, "Process ID is:\t %d \n", getpid());
        snprintf(hName, 128, "Hostname is:\t %s \n\n", hostname);

        char name[128];
        char version[128];
        char release[128];

        // The library utsname provides us the details object
        // We will store these messages into the char arrays
        snprintf(name, 128, "OS name is:\t %s \n", details.machine);
        snprintf(version, 128, "OS release is:\t %s \n", details.version);
        snprintf(release, 128, "OS version is:\t %s \n\n", details.release);

        char *buffer;

        // Here i am error checking the current working directory and storing it into buffer
        if ((buffer = getcwd(NULL, 0)) == NULL)
        {
            perror("failed to get current directory\n");
        }
        else
        {
            snprintf(direct, 128, "Process current working directory is:\t %s \n", buffer);
            free(buffer);
        }

        // These following while loops are all to find the length of the strings since we cant use strlen()
        int u = 0;
        while (ppidmsg[u] != '\0')
        {
            u++;
        }
        write(STDOUT_FILENO, ppidmsg, u);
        u = 0;
        while (pidmsg[u] != '\0')
        {
            u++;
        }
        write(STDOUT_FILENO, pidmsg, u);
        u = 0;
        while (direct[u] != '\0')
        {
            u++;
        }
        write(STDOUT_FILENO, direct, u);
        u = 0;
        while (hName[u] != '\0')
        {
            u++;
        }
        write(STDOUT_FILENO, hName, u);

        u = 0;
        while (name[u] != '\0')
        {
            u++;
        }
        write(STDOUT_FILENO, name, u);
        u = 0;
        while (version[u] != '\0')
        {
            u++;
        }
        write(STDOUT_FILENO, version, u);
        u = 0;
        while (release[u] != '\0')
        {
            u++;
        }
        write(STDOUT_FILENO, release, u);

        // since we only write to the pipe, we can close the read end of the pipe
        close(fd[0]);
        int f1;
        int len = 0;
        int j = 0;
        // finding the length of input file name
        while (INPUT_FILE[j] != '\0')
        {
            j++;
            len++;
        }
        len++;
        // Open input file
        if ((f1 = open(INPUT_FILE, O_RDONLY, 0)) == -1)
        {
            printf("Can't open %s \n", INPUT_FILE);
            return 2;
        }
        int n;
        int count = 0;
        char buf[BUFFER_SIZE * 100];
        // Write the length of input file into pipe
        write(fd[1], &len, sizeof(int));
        // Write contents of input file name into pipe
        write(fd[1], INPUT_FILE, len);

        // We read the whole file until theres nothing left to read
        while ((n = read(f1, buf, BUFFER_SIZE * 100)) > 0)
        {
            // Adding up the ammount of characters read
            count += n;
        }

        // Write size of content to pipe
        write(fd[1], &count, sizeof(int));
        // Write contents of file into pipe
        write(fd[1], buf, count);

        // Done with pipe and files so we can close them
        close(f1);
        close(fd[1]);

        // Message queuee
        unsigned int prio;
        struct timespec timeout = {0, 0};

        // Struct used for multiple messages
        Message msg;

        // Create blocking recived messages and store contents into msg
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

        // Print out contents to output based on OPTIONS you specified
        if (nLine == 1)
            write(STDOUT_FILENO, msg.newLine, len1);
        if (words == 1)
            write(STDOUT_FILENO, msg.words, len2);
        if (chars == 1)
            write(STDOUT_FILENO, msg.character, len3);
        if (maxL == 1)
            write(STDOUT_FILENO, msg.maxLine, len4);
        write(STDOUT_FILENO, "\n", 1);

        // Unlink queue
        mq_close(queue);
        mq_unlink(MQ_NAME);

        // Terminate child process
        write(STDOUT_FILENO, "Child: Terminating.\n", 20);
    }
    else
    {
        // Close write end of pipe since we will only we reading from it
        close(fd[1]);
        char line[BUFFER_SIZE * 100];
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

        // This for loop contains the basic logic for words, characters, newlines etc...
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == ' ')
            {
                curL++;
                count++;
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

        // Paste messages into the msg object based on results recived from the child pipe
        Message msg;
        strcpy(msg.msg, line);
        snprintf(msg.newLine, 128, "%s:\t newline count is:\t %d \n", file, newLine);
        snprintf(msg.character, 128, "%s:\t character count is:\t %d \n", file, len);
        snprintf(msg.maxLine, 128, "%s:\t maximum line length is:\t %d \n", file, max);
        snprintf(msg.words, 128, "%s:\t word count is:\t %d \n", file, words);

        // Create blocking send message
        if (mq_timedsend(queue, (char *)&msg, sizeof(Message), 1, NULL) == -1)
        {
            printf("Parent: mq_send error\n");
            return 4;
        }

        // close file descriptors and unlink the queue
        close(fd[0]);
        mq_close(queue);
        mq_unlink(MQ_NAME);
        wait(NULL);
        write(STDOUT_FILENO, "Parent: Terminating.\n", 21);
    }

    return 0;
}
