#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Account.hpp"
#include <iostream>

key_t key1 = 1234;

int N = GetAccountNum();

void checkBalance (int accountNum) {
	if (accountNum >= N) {
		std::cout << "There isn't " << accountNum << " account!" << std::endl;
	}
	int shmid1;
	AccountAttr* shm1;

        shmid1 = shmget(key1, 0 , 0);
        if(shmid1 == -1) {
                perror("shmget1");
                exit(1);
        }
        shm1 = (AccountAttr*)shmat(shmid1, NULL , 0);
        if(shm1 ==(void*)-1) {
                perror("shmat1");
                exit(1);
        }
	for(int i = 1 ; i < N * 5 ; i += 5) {
		if (shm1[i].numAccount == accountNum) {
			if(shm1[i].frozenAccount == true) {
				std::cout << "Dear customer , your card has been frozen!" << std::endl;
			}
			else {
				std::cout << "Dear customer , your current balance is:"<< shm1[i].currentBalance << "$" << std::endl;
				std::cout << "Min Balance is:" << shm1[i].minBalance << "$" << std::endl;
				std::cout << "Max Balance is:" << shm1[i].maxBalance << "$" << std::endl;
			}
		}
	}
}

void creditedBalance (int addSum) {
	int shmid1;
	AccountAttr* shm1;

        shmid1 = shmget(key1, 0 , 0);
        if(shmid1 == -1) {
                perror("shmget2");
                exit(1);
        }
        shm1 = (AccountAttr*)shmat(shmid1, NULL , 0);
        if(shm1 ==(void*)-1) {
                perror("shmat2");
                exit(1);
        }
        for(int i = 1 ; i < N * 5 ; i += 5) {
		int checkCurrentBalance = shm1[i].currentBalance + addSum;
		if (checkCurrentBalance > shm1[i].maxBalance) {
			std::cout <<"Dear customer , you can't credit your account" << std::endl;
		}
		else if (shm1[i].frozenAccount == true) {
                        std::cout << "Dear customer , your card has been frozen!" << std::endl;
                }
		else {
			shm1[i].currentBalance += addSum;
		        std::cout << "Dear customer , your card has been credited by:"<<  addSum << "$" << std::endl;
		}
        }
        
}

void chargedBalance (int subSum) {
        int shmid1;
        AccountAttr* shm1;

        shmid1 = shmget(key1, 0 , 0);
        if(shmid1 == -1) {
                perror("shmget3");
                exit(1);
        }
        shm1 = (AccountAttr*)shmat(shmid1, NULL , 0);
        if(shm1 ==(void*)-1) {
                perror("shmat3");
                exit(1);
        }
        for(int i = 1 ; i < N * 5 ; i += 5) {
		int checkCurrentBalance = shm1[i].currentBalance - subSum;
		if (checkCurrentBalance < shm1[i].minBalance) {
                        std::cout <<"Dear customer , you can't charge your account" << std::endl;
                }
		else if(shm1[i].frozenAccount == true) {
                        std::cout << "Dear customer , your card has been frozen!" << std::endl;
                }
		else {
                       	shm1[i].currentBalance -= subSum;
			std::cout << "Dear customer , your card has been charged by:"<<  subSum << "$" << std::endl;
		}
        }
}

void frozenAccount (int accountNum , bool f) {
	if (accountNum >= N) {
                std::cout << "There isn't " << accountNum << " account!" << std::endl;
        }
        int shmid1;
        AccountAttr* shm1;

        shmid1 = shmget(key1, 0 , 0);
        if(shmid1 == -1) {
                perror("shmget4");
                exit(1);
        }
        shm1 = (AccountAttr*)shmat(shmid1, NULL , 0);
        if(shm1 ==(void*)-1) {
                perror("shmat4");
                exit(1);
        }
	for(int i = 1 ; i < N * 5 ; i += 5) {
                if (shm1[i].numAccount == accountNum) {
                        shm1[i].frozenAccount = f;
			if (f == true) {
                        	std::cout << "Dear customer , your card has been frozen!" << std::endl;
			}
			else {
				std::cout << "Dear customer , your card has been not frozen!" << std::endl;
			}
                }
        }

}

void transferMoney (int sourceAccountNum , int targetAccountNum , int transferSum) {
	if (sourceAccountNum >= N) {
                std::cout << "There isn't " << sourceAccountNum << " account!" << std::endl;
		exit(1);
        }
	if (targetAccountNum >= N) {
                std::cout << "There isn't " << targetAccountNum << " account!" << std::endl;
                exit(1);
        }
        int shmid1;
        AccountAttr* shm1;

        shmid1 = shmget(key1, 0 , 0);
        if(shmid1 == -1) {
                perror("shmget4");
                exit(1);
        }
        shm1 = (AccountAttr*)shmat(shmid1, NULL , 0);
        if(shm1 ==(void*)-1) {
                perror("shmat4");
                exit(1);
        }

        for(int i = 1 ; i < N * 5 ; i += 5) {
		if (shm1[i].numAccount == sourceAccountNum) {
			if (shm1[i].frozenAccount == true) {
                              std::cout << "Dear customer , your card has been frozen!" << std::endl;
                        }
                        else if (shm1[i].currentBalance - transferSum < shm1[i].minBalance) {
                              std::cout << "Dear customer , your can't transfer so much money!" << std::endl;
                        }
 			else {
                        	shm1[i].currentBalance -= transferSum;
				std::cout << "Dear customer , you transfer " << transferSum << "$" << std::endl; 
			}
                }

		if (shm1[i].numAccount == targetAccountNum) {
                      if (shm1[i].frozenAccount == true) {
                              std::cout << "Dear customer , your card has been frozen!" << std::endl;
                       }
		      else if (shm1[i].currentBalance + transferSum > shm1[i].maxBalance) {
                                std::cout << "Dear customer , your can't transfer so much money!" << std::endl;
                      }
		      else {
				shm1[i].currentBalance += transferSum;
                	        std::cout << "Done!" << std::endl;
		      }
                }
        }

}

void changeMaxBalance(int accountNum , int newMaxBalance) {
	if (accountNum >= N) {
                std::cout << "There isn't " << accountNum << " account!" << std::endl;
        }
	int shmid1;
        AccountAttr* shm1;

        shmid1 = shmget(key1, 0 , 0);
        if(shmid1 == -1) {
                perror("shmget4");
                exit(1);
        }
        shm1 = (AccountAttr*)shmat(shmid1, NULL , 0);
        if(shm1 ==(void*)-1) {
                perror("shmat4");
                exit(1);
        }

	for(int i = 1 ; i < N * 5 ; i += 5) {
		if (shm1[i].frozenAccount == true) {
			std::cout << "Dear customer , your card has been frozen!" << std::endl;
		}
		else if (shm1[i].numAccount == accountNum) {
                        shm1[i].maxBalance = newMaxBalance;
                        std::cout << "Dear customer , your max balance now is " << newMaxBalance << "$" << std::endl;
                }
        }

}

void changeMinBalance(int accountNum , int newMinBalance) {
	if (accountNum >= N) {
                std::cout << "There isn't " << accountNum << " account!" << std::endl;
        }
	int shmid1;
        AccountAttr* shm1;

        shmid1 = shmget(key1, 0 , 0);
        if(shmid1 == -1) {
                perror("shmget5");
                exit(1);
        }
        shm1 = (AccountAttr*)shmat(shmid1, NULL , 0);
        if(shm1 ==(void*)-1) {
                perror("shmat5");
                exit(1);
        }

        for(int i = 1 ; i < N * 5 ; i += 5) {
                if (shm1[i].frozenAccount == true) {
                        std::cout << "Dear customer , your card has been frozen!" << std::endl;
                }
                else if (shm1[i].numAccount == accountNum) {
                        shm1[i].minBalance = newMinBalance;
                        std::cout << "Dear customer , your min balance now is " << newMinBalance << "$" << std::endl;
                }
        }

}



int main (int argc , char** argv) {
	std::string op;
	int accountNum;
	while (true) {
		std::cout << "Choose one of this" << std::endl;
		std::cout << "???" << std::endl;
		std::cout << ".checkBalance" << std::endl;
		std::cout << ".crediteBalance" << std::endl;
		std::cout << ".chargeBalance" << std::endl;
		std::cout << ".frozeAccount" << std::endl;
		std::cout << ".unfrozeAccount" << std::endl;
		std::cout << ".changeMinBalance" << std::endl;
		std::cout << ".changeMaxBalance" << std::endl;
		std::cout << ".transferMoney" << std::endl;
		std::cout << ".nothing" << std::endl;
		std::cin >> op;
		if (op == "checkBalance") {
			std::cout << "PLease enter accountNum" << std::endl;
			std::cin >> accountNum;
			checkBalance(accountNum);
		}
		else if (op == "crediteBalance") {
			int addSum;
			std::cout << "Please enter sum" << std::endl;
			std::cin >> addSum; 
			creditedBalance(addSum);
		}
		else if (op == "chargeBalance") {
			int sumSum;
			std::cout << "Please enter sum" << std::endl;
			std::cin >> sumSum;
			chargedBalance(sumSum);
		}
		else if (op == "frozeAccount") {
			std::cout << "PLease enter accountNum" << std::endl;
			std::cin >> accountNum;
			frozenAccount(accountNum, true);
		}
		else if (op == "unfrozeAccount") {
			std::cout << "PLease enter accountNum" << std::endl;
			std::cin >> accountNum;
			frozenAccount(accountNum, false);
		}
		else if (op == "changeMinBalance") {
			std::cout << "PLease enter accountNum" << std::endl;
			std::cin >> accountNum;
			int newMinBalance;
			std::cout << "Please enter new min Balance" << std::endl;
			std::cin >> newMinBalance;
			changeMinBalance(accountNum, newMinBalance);
		}
		else if (op == "changeMaxBalance") {
			std::cout << "PLease enter accountNum" << std::endl;
			std::cin >> accountNum;
			int newMaxBalance;
			std::cout << "PLease enter new max Balance" << std::endl;
			std::cin >> newMaxBalance;
			changeMaxBalance(accountNum, newMaxBalance);
		}
		else if (op == "transferMoney") {
			std::cout << "Enter sourceAccount num" << std::endl;
			std::cin >> accountNum;
			int targetAccount;
			int sum;
			std::cout << "Enter targetAccount num" << std::endl;
			std::cin >> targetAccount;
			std::cout << "PLease enter sum" << std::endl;
			std::cin >> sum;
			transferMoney(accountNum , targetAccount, sum);
		}
		else if (op =="nothing") {
			break;
		}
		else {
			std::cout << "There isn't that lind of operation. Choose again!" << std::endl;
		}
	}



	//checkBalance void checkBalance (int accountNum) 
	//credited void creditedBalance(int addSum)
	//charged void chargedBalance (int subSum)
	//frozed void frozenAccount (int accountNum , bool f) 
	//unfrozed void frozenAccount (int accountNum , bool f) 
	//changeMinBalance void changeMinBalance(int accountNum , int newMinBalance)
	//changeMaxBalance void changeMaxBalance(int accountNum , int newMaxBalance) 
	//transferMoney void transferMoney (int sourceAccountNum , int targetAccountNum , int transferSum)
	//nothing break
}
