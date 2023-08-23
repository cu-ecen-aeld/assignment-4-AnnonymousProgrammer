#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    if(thread_param != NULL){
    	    struct thread_data * thread_func_args = (struct thread_data *) thread_param;
    	    thread_func_args->thread_complete_success = false;
	    usleep(thread_func_args->wait_to_obtain_ms * 1000);
	    //printf("trying to acquire mutex");
	    pthread_mutex_lock(thread_func_args->mutex);
	    usleep(thread_func_args->wait_to_release_ms * 1000);
	    //printf("trying to unlock mutex");
	    pthread_mutex_unlock(thread_func_args->mutex);
	    thread_func_args->thread_complete_success = true;
    }
    
    
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
     
     struct thread_data * ptr = (struct thread_data *)  malloc(sizeof(struct thread_data));
     if(ptr != NULL){
     	ptr->wait_to_obtain_ms = wait_to_obtain_ms;
     	ptr->wait_to_release_ms = wait_to_release_ms;
     	ptr->mutex = mutex;
     	pthread_t my_thread;
     	int rc1 = pthread_create(&my_thread, NULL, threadfunc, (void *) ptr);
     	if(rc1 != 0){
     		return false;
     	}
     	//int rc2 = pthread_join(my_thread, NULL);
     	//if(rc2 != 0){
     	//	return false;
     	//}
     	//if(ptr->thread_complete_success == true){
     	*thread = my_thread;
     		
     	//}
     	//free(ptr);
     	return true;
     	
     }
     
     
    return true;
}

/**
int main(){
	pthread_t t;
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	start_thread_obtaining_mutex(&t, &mutex, 10, 10);
}
**/

