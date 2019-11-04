#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "log.h"

//pthread_mutex_t rdLock = PTHREAD_MUTEX_INITIALIZER;
pthread_rwlock_t rwlock;

void my_lock(void* wdLock, int lock)
{
	printf("my_lock...\n");
	if(lock == 1){
		printf("lock...\n");
		pthread_rwlock_wrlock((pthread_rwlock_t *)wdLock);
	}else{
		printf("unlock...\n");
		pthread_rwlock_unlock((pthread_rwlock_t*)wdLock);
	}
}

#define beQuiet	1


int main(int argc, char** argv)
{
	// preparing time
	pthread_rwlock_init(&rwlock, NULL);
	log_set_quiet(beQuiet);

	log_set_level(LOG_TRACE);

	FILE* fp = fopen("./test.log", "a+");
	if(!fp){
		printf("Failed to open file.\n");
		return -1;
	}

	log_set_fp(fp);

	log_set_udata(&rwlock);

	log_set_lock(my_lock);

	log_info("Hello, world\n");

	pthread_rwlock_destroy(&rwlock);
	return 0;
}
