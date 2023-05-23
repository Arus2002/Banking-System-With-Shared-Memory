#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Account.hpp"


int shmid;
AccountAttr* shm;
key_t key = 1234;
int* shmForN;

void Initialiser (int AccountCount) {

	int size = (AccountCount * sizeof(AccountAttr)) + sizeof(int);
	//sarqecinq
	shmid = shmget(key, size, IPC_CREAT | 0666);
	if(shmid == -1) {
		perror("shmget3");
		exit(1);
	}
	shmForN = (int*)shmat(shmid, NULL, 0);
	if(shmForN ==(void*)-1) {
                perror("shmat");
                exit(1);
        }
	//kpcrecinq processin
	shm = (AccountAttr*)shmat(shmid, NULL, 0);
	if(shm ==(void*)-1) {
		perror("shmat");
		exit(1);
	}
	//lcrecinq shared memeory-n
	int count = 0;
        for(int i = 1; i < AccountCount * 5; i += 5) {
		shm[i].numAccount = count;
	        shm[i].currentBalance = 0;
		shm[i].minBalance = 0;
		shm[i].maxBalance = 1000000;
		shm[i].frozenAccount = false;
	        count++;	
	}
	shmForN[0] = count;

	std::cout << AccountCount << " " << "Accounts were created!" << std::endl;
		
}

int main(int argc, char** argv) {
	if (argc < 2) {
		perror("argc");
		exit(1);
	}
	int N;
	N = std::stoi(argv[1]);
	Initialiser(N);
}

