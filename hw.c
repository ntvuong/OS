#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>  //for errno, the number of last error
#include <unistd.h> //fork, pipe
#include <time.h>   //time
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>    // S_IRUSR, etc
#include <sys/time.h> //random
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h> //waitpid

struct data{
    char address[100];
    int area;
    int k;
    char listOfTask[100][100];
    char deadline[100];
};

void menu()
{
    int option = 0;

    do{
        printf("HOME: Choose one number \n [0-Exit]"
                     "\n [1-Register order] \n [2-List all order]"
                     "\n [3-Modify order] \n [4-Delete order] \n [5-Add Order] \n");
        scanf("%d", &option);

        switch(option){
            case 1:
                registerCustomer();
                break;
            case 2:
                listCustomer();
                break;
            case 3:
                modifyOrder();
                break;
            case 4:
                deleteOrder();
                break;
            case 5:
                addOrder();
                break;
            case 6:
                listToFile();
				break;
			case 7:
				//findShortestDeadline();
				break;
            default:
                break;
        }
    }
    while (option != 0);
}

int n = 0;
struct data arrayCustomer[100];
int i = 0;
//int k = 0;

void registerCustomer(){
    printf("How many customers do you want to register?\n");
    scanf("%d", &n);
    printf("Type in the customer's information: \n");
    getchar();
    for (i = 0; i < n; i++){
        printf("Customer No.%d: ", i + 1);
        printf("\nAddress: ");
        //fflush(stdin);
        //gets(arrayCustomer[i].address);
	fgets(arrayCustomer[i].address, 100, stdin);
        printf("Area: ");
        int temp = 0;
        scanf("%d", &temp);
        arrayCustomer[i].area = temp;
        int j = 0;
        printf("Number of task: ");
        scanf("%d", &arrayCustomer[i].k);
        getchar();
        for (j = 0; j < arrayCustomer[i].k; j++){
            printf("Task No.%d: ", j + 1);
            fgets(arrayCustomer[i].listOfTask[j], 100, stdin);
        }
        /*for (j = 0; j < arrayCustomer[i].k; j++){
            printf("Task No.%d: ", j + 1);
            printf("%s", arrayCustomer[i].listOfTask[j]);
        }*/
        printf("Deadline: ");
        fflush(stdin);
        gets(arrayCustomer[i].deadline);
    }
    listToFile();
}

void listCustomer(){
    int h = 0;
    for (i = 0; i < n; i++){
        printf("\nCustomer No.%d: ", i + 1);
        printf("\nAddress: %s", arrayCustomer[i].address);
        printf("\nArea: %d \n", arrayCustomer[i].area);
        for (h = 0; h < arrayCustomer[i].k; h++){
            printf("Task No.%d: ", h + 1);
            printf("%s", arrayCustomer[i].listOfTask[h]);
        }
        printf("Deadline: %s\n", arrayCustomer[i].deadline);
    }
    listToFile();
}

void modifyOrder(){
    int pos = 0;
    printf("Enter the position of order where you wish to modify\n");
    scanf("%d", &pos);
    //n = n - 1;
    if (pos >= n + 1){
        printf("Modification is not possible.\n");
    }
    else{
        getchar();
        printf("Customer No.%d: ", pos);
        printf("\nAddress: ");
        //fflush(stdin);
        fgets(arrayCustomer[pos - 1].address, 100, stdin);
        printf("Area: ");
        int temp = 0;
        scanf("%d", &temp);
        arrayCustomer[pos - 1].area = temp;
        int j = 0;
        printf("Number of task: ");
        scanf("%d", &arrayCustomer[pos - 1].k);
        getchar();
        for (j = 0; j < arrayCustomer[pos - 1].k; j++){
            printf("Task No.%d: ", j + 1);
            fgets(arrayCustomer[pos - 1].listOfTask[j], 100, stdin);
        }
        /*for (j = 0; j < arrayCustomer[i].k; j++){
            printf("Task No.%d: ", j + 1);
            printf("%s\n", arrayCustomer[i].listOfTask[j]);
        }*/
        printf("Deadline: ");
        fflush(stdin);
        gets(arrayCustomer[pos - 1].deadline);
    }
    listToFile();
}

void deleteOrder(){
    //printf("\n%d\n", n);
    int pos = 0;
    printf("Enter the position of order where you wish to delete\n");
    scanf("%d", &pos);
    //n = n - 1;
    if (pos >= n + 1){
        printf("Deletion is not possible.\n");
    }
    else{
        n = n - 1;
        for (i = pos - 1; i < n; i++){
            arrayCustomer[i] = arrayCustomer[i + 1];
        }
    }
    int h = 0;
    for (i = 0; i < n; i++){
        printf("\nCustomer No.%d: ", i + 1);
        printf("\nAddress: %s", arrayCustomer[i].address);
        printf("\nArea: %d", arrayCustomer[i].area);
        for (h = 0; h < arrayCustomer[i].k; h++){
            printf("\nTask No.%d: ", h + 1);
            printf("%s", arrayCustomer[i].listOfTask[h]);
        }
        printf("\nDeadline: %s \n", arrayCustomer[i].deadline);
    }
    listToFile();
}

void addOrder(){
    n = n + 1;
    getchar();
    printf("Customer No.%d: ", n);
    printf("\nAddress: ");
    //fflush(stdin);
    //gets(arrayCustomer[i].address);
    fgets(arrayCustomer[i].address, 100, stdin);
    printf("Area: ");
    int temp = 0;
    scanf("%d", &temp);
    arrayCustomer[i].area = temp;
    int j = 0;
    printf("Number of task: ");
    scanf("%d", &arrayCustomer[i].k);
    getchar();
    for (j = 0; j < arrayCustomer[i].k; j++){
        printf("Task No.%d: ", j + 1);
        fgets(arrayCustomer[i].listOfTask[j], 100, stdin);
    }
    /*for (j = 0; j < arrayCustomer[i].k; j++){
        printf("Task No.%d: ", j + 1);
        printf("%s\n", arrayCustomer[i].listOfTask[j]);
    }*/
    printf("Deadline: ");
    fflush(stdin);
    gets(arrayCustomer[i].deadline);
    listToFile();
}

void listToFile(){
    FILE *fp;
    fp = fopen("output.txt", "w+");
    int h = 0;
    for (i = 0; i < n; i++){
        fprintf(fp, "\nCustomer No.%d: ", i + 1);
        fprintf(fp, "\nAddress: %s", arrayCustomer[i].address);
        fprintf(fp, "\nArea: %d \n", arrayCustomer[i].area);
        for (h = 0; h < arrayCustomer[i].k; h++){
            fprintf(fp, "Task No.%d: ", h + 1);
            fprintf(fp, "%s", arrayCustomer[i].listOfTask[h]);
        }
        fprintf(fp, "Deadline: %s\n", arrayCustomer[i].deadline);
    }
    fclose(fp);
}


struct MsgBuffer
{
	long mtype;
	char mtext[420];
};


int compareDateFormat(char deadline[100])
{
	int year = 0 ,month = 0 ,day = 0;
	char slash = '/';

	sscanf(deadline, "%d%c%d%c%d", &year, &slash, &month, &slash, &day);

	return (year + month + day);
}

/*int findShortestDeadline()
{
	int min = 0;
	for (i = 0; i < n; i++)
	{
		if (compareDateFormat(arrayCustomer[i].deadline) < compareDateFormat(arrayCustomer[min].deadline))
		{
			min = i;
			printf("%d\n", min);
			return min + 1;
		}
	}
	//printf("%d\n", min);
	//return min + 1;
}*/

int compare()
{
    int min = 0;
	for (i = 0; i < n; i++)
	{
		if (compareDateFormat(arrayCustomer[i].deadline) < compareDateFormat(arrayCustomer[min].deadline))
		{
			min = i;
		}
	}
	//printf("%d", min);
	return min;
}

void handler(int signumber)
{
    printf("Signal %d has arrived for %d!\n", signumber, getpid());
}

int main(int argc, char **argv)
{
	// Signals
    struct sigaction sigact;
    sigact.sa_handler = handler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGUSR1, &sigact, NULL);
    // Setup wait
    sigset_t sigset;
    sigfillset(&sigset);
    sigdelset(&sigset, SIGUSR1);
	
	registerCustomer(); //or void menu()
	
	srand(time(NULL));
	
	// PIPE
	int pipefd[2]; // unamed pipe
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	// MSGQUEUE
	key_t key;
	int msqid;
	if ((key = ftok(argv[0], 'V')) == -1)
	{
		perror("ftok failed");
		exit(EXIT_FAILURE);
	}
	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1)
	{
		perror("msgget failed");
		exit(EXIT_FAILURE);
	}
	
	// FORK
	pid_t worker = fork();
	if (worker > 0)
	{
		printf("This is the Firm!\n");
		// Wait
        printf("Waiting for the team\n");
        sigsuspend(&sigset);
        printf("The team is ready\n");

        close(pipefd[0]); // Unused read end
		
		
		int m = compare();
		close(pipefd[0]); 
		printf("The Firm is giving info:\n");
		struct data *work = &arrayCustomer[m];
		char num[10];
		write(pipefd[1], work->address, 100);
		sprintf(num, "%d", work->k);
		write(pipefd[1], num, 100);
		int h;
		for(h = 0; h < work->k; h++)
		{
			write(pipefd[1], work->listOfTask[h], 100);
		}
		
		// Receive msg
		wait(NULL); 
		struct MsgBuffer buf;
		int status;
		status = msgrcv(msqid, &buf, 420, 13, 0);
		if (status < 0)
		{
			perror("msgrcv");
		}
		else
		{
			printf("Task status: %s\n", buf.mtext);
		}
		// Remove the queue
		status = msgctl(msqid, IPC_RMID, NULL);
		if (status < 0)
			perror("msgctl");
		
		close(pipefd[1]);
	}
	else if (worker == 0)
	{ // child process
		printf("This is the Team\n");
		printf("Team: %d\n", getpid());
        sleep(1);
        kill(getppid(), SIGUSR1);

        close(pipefd[1]);     // Unused write end
		// Read the received work
		char info[100];
		printf("The received info:\n");
		read(pipefd[0], info, sizeof(info));
		printf("%s\n", info);
		read(pipefd[0], info, sizeof(info));
		int num = atoi(info);
		int i;
		for(i = 0; i < num; ++i)
		{
			read(pipefd[0], info, sizeof(info));
			printf("%s\n", info);
		}
		// Working
		int percent = rand() % 100;
		//printf("Success percent: %d\n", percent);
		bool finished = percent >= 10;
		struct MsgBuffer buf = {13, ""};
		if (finished)
			strcpy(buf.mtext, "success ahoehoe");
		else
			strcpy(buf.mtext, "missed ahuhu");
		// Send msg
		int status = msgsnd(msqid, &buf, strlen(buf.mtext) + 1, 0);
		if (status < 0)
		{
			perror("msgsnd failed");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
	}
	else
	{ // fork error
		perror("fork");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}























