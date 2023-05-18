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

void Initialiser (int AccountCount) {

	int size = AccountCount * sizeof(AccountAttr);
	//sarqecinq
	shmid = shmget(key, size, IPC_CREAT | 0666);
	if(shmid == -1) {
		perror("shmget");
		exit(1);
	}
	//kpcrecinq processin
	shm = (AccountAttr*)shmat(shmid, NULL, 0);
	if(shm ==(void*)-1) {
		perror("shmat");
		exit(1);
	}
	//lcrecinq shared memeory-n
        for(int i = 0; i < AccountCount * 4; i += 4) {
	        shm[i].CurrentBalance = 0;
		shm[i].MinBalance = 0;
		shm[i].MaxBalance = 1000000;
		shm[i].FrozenAccount;
	}
	std::cout << AccountCount << " " << "Accounts were created!" << std::endl;
		
}
int main(int argc , char** argv) {
	int N;
	N = std::atoi(argv[1]);
	Initialiser(N);

}


