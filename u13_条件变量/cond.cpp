/*
NAME
       pthread_cond_destroy, pthread_cond_init - destroy and initialize condition variables

SYNOPSIS
       #include <pthread.h>

       int pthread_cond_destroy(pthread_cond_t *cond);
       int pthread_cond_init(pthread_cond_t *restrict cond,
              const pthread_condattr_t *restrict attr);
       pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
######################################################################
NAME
       pthread_cond_timedwait, pthread_cond_wait - wait on a condition

SYNOPSIS
       #include <pthread.h>

       int pthread_cond_timedwait(pthread_cond_t *restrict cond,
              pthread_mutex_t *restrict mutex,
              const struct timespec *restrict abstime);
       int pthread_cond_wait(pthread_cond_t *restrict cond,
              pthread_mutex_t *restrict mutex);
#######################################################################
NAME
       pthread_cond_broadcast, pthread_cond_signal - broadcast or signal a condition

SYNOPSIS
       #include <pthread.h>

       int pthread_cond_broadcast(pthread_cond_t *cond);
       int pthread_cond_signal(pthread_cond_t *cond);
*/


int main(){
    
    return 0;
}