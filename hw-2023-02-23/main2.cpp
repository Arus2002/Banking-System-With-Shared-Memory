#include <iostream>
#include <pthread.h>

int done = 0;
int count = 0;
pthread_mutex_t m1;
pthread_mutex_t m2;
pthread_mutex_t m3;
pthread_cond_t c;

void* pthread_foo1() {
        pthread_mutex_lock(&m2);
        while(done) {
                return NULL;
        }
        pthread_mutex_unlock(&m2);
	return NULL;

}

void pthread_exit() {
        pthread_mutex_lock(&m2);
        done == 1;
        pthread_cond_signal(&c);
        pthread_mutex_lock(&m2);
}


void* CountOfCharacters1 (void* arg) {
	char mainstr = ' ';
	while(std::cin >> mainstr) {
		pthread_mutex_lock(&m1);
		count++;
		pthread_cond_signal(&c);
		pthread_mutex_unlock(&m1);;
	}
	pthread_mutex_lock(&m3);
	std::cout <<"Total count of symbols: " <<  count << std::endl;
	pthread_mutex_unlock(&m3);
	pthread_exit();
	pthread_exit(NULL);

	
}
void* CountOfCharacters2 (void* arg) {
	pthread_mutex_lock(&m1);
	while(count < 10) {
		pthread_cond_wait(&c , &m1);
		pthread_foo1();
	}
	pthread_mutex_lock(&m3);
        std::cout << "Count is >10" << std::endl;
        pthread_mutex_unlock(&m3);
	while(count < 50) {
                pthread_cond_wait(&c , &m1);
                pthread_foo1();
        }
        pthread_mutex_lock(&m3);
        std::cout << "Count is >50" << std::endl;
        pthread_mutex_unlock(&m3);
	pthread_mutex_unlock(&m1);
	pthread_exit(NULL);
	
	
}

int main(int argc , char** argv) {
	pthread_t tid[2];
	pthread_mutex_init(&m1 , NULL);
	pthread_cond_init(&c , NULL);
	for(int i = 0 ; i < 2 ; ++i) {
		if(i == 1) {
			if(pthread_create(&tid[i] , NULL , &CountOfCharacters2  , NULL ) != 0 ) {
				return 1;
			}
		}
		else {
			if(pthread_create(&tid[i] , NULL , CountOfCharacters1  , NULL ) != 0 ) {
               			return 1;
       			}
		}
	}
	for(int i = 0 ; i < 2 ; ++i) {
		if(pthread_join(tid[i] , NULL) != 0) {
			return 1;
		}	
	}
	pthread_mutex_destroy(&m1);
	pthread_cond_destroy(&c);
}
