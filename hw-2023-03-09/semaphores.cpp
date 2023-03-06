#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

int N;

void update (int sem_id , int number) {
        struct sembuf sem_op;

        sem_op.sem_num = 0; 
        sem_op.sem_op = -1; 
        sem_op.sem_flg = 0;
        semop(sem_id , &sem_op , 1); 
        std::cout << "I am process:" << number << std::endl;

        sem_op.sem_num = 0;
        sem_op.sem_op = 1;
        sem_op.sem_flg = 0;
        semop(sem_id , &sem_op , 1);
}

void do_child (int sem_id) {
	for(int i = 1 ; i <= N ; ++i) {
		update(sem_id , i);
	}	
}

int main(int argc , char** argv) {
	N = atoi(argv[1]);
	int sem_id;
	sem_id = semget(IPC_PRIVATE , 1 , IPC_CREAT | 0600);
	if(sem_id == -1) {
		return 1;
	}
	int sem_id2;
	sem_id2 = semctl(sem_id , 0 , IPC_RMID , 0);
	if(sem_id2 == -1) {
		return 1;
	}

	pid_t pid;
	for(int i = 1 ; i <= N ; ++i) {
		pid = fork();
		if(pid == -1) {
			perror("fork");
			return 1;
		}
		else if(pid == 0) {
			do_child(sem_id);
			exit(0);
		}
		else {
			break;
		}
	}
	for(int i = 0 ; i < N ; ++i) {
		wait(NULL);
	}

}

