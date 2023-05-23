#include <iostream>
#ifndef ACCOUNT
#define ACCOUNT

key_t key2 = 1234;

struct AccountAttr {
        int currentBalance;
        int minBalance;
        int maxBalance;
	int numAccount;
        bool frozenAccount;
};

int GetAccountNum() {
	int shmid1;
        int* shmForN;

        shmid1 = shmget(key2, 0 , 0);
        if(shmid1 == -1) {
                perror("shmget5");
                exit(1);
        }
        shmForN = (int*)shmat(shmid1, NULL , 0);
        if(shmForN ==(void*)-1) {
                perror("shmat5");
                exit(1);
        }
        int N;
        N = shmForN[0];
	return N;

}

#endif

