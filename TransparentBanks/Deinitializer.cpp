#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Account.hpp"


key_t key = 1234;

void Deinitialiser () {
	int shm;
	//stextsecinq
	int shmid = shmget(key, 0 , 0);
	if(shmid == -1) {
		perror("shmget");
		exit(1);
	}
	//anjatecinq
       	shmdt((shmat(shmid , NULL , 0)));
	//azatecinq shared memory-n
	shm = shmctl(shmid , IPC_RMID , 0);
	if(shm == -1) {
		perror("shmctl");
		exit(1);
	}
	std::cout << "Accounts were destroyed!" << std::endl;	
	
}

int main(int argc , char** argv) {
	Deinitialiser();
}
