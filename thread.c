#include "types.h"
#include "stat.h"
#include "x86.h"
#include "user.h"
#include "syscall.h"
#include "spinlock.h"

struct balance {
    char name[32];
    int amount;
};

struct thread_spinlock {
    uint locked;       // Is the lock held?
};

struct thread_mutex {
  uint locked;
}

volatile int total_balance = 0;
static struct thread_spinlock lock;
static struct thread_mutex mlock;

volatile unsigned int delay (unsigned int d) {
   unsigned int i; 
   for (i = 0; i < d; i++) {
       __asm volatile( "nop" ::: );
   }

   return i;   
}

// spin lock thread
void thread_spin_init(struct thread_spinlock *lk) {
  lk->locked = 0;
}

void thread_spin_lock(struct thread_spinlock *lk) {
  // do not need holding because this thread only has one purpose
  // The xchg is atomic.
  while(xchg(&lk->locked, 1) != 0)
    ;

  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that the critical section's memory
  // references happen after the lock is acquired.
  __sync_synchronize();

}

void thread_spin_unlock(struct thread_spinlock *lk) {
  __sync_synchronize();
  asm volatile("movl $0, %0" : "+m" (lk->locked) : );
}

// mutex
void thread_mutex_init(struct thread_mutex *lk) {
  lk->locked = 0;
}

void thread_mutex_lock(struct thread_mutex *lk) {
  while( xchg(&lk->locked) != 0 )
    // release cpu for scheduler
    sleep(1);
  __sync_synchronize();
}

void thread_mutex_unlock(struct thread_mutex *lk) {
  __sync_synchronize();
  lk->locked = 0;
}

// parallel works
void do_work(void *arg){
    int i; 
    int old;
   
    struct balance *b = (struct balance*) arg; 
    printf(1, "Starting do_work: s:%s\n", b->name);

    for (i = 0; i < b->amount; i++) { 
        // thread_spin_lock(&lock);
        thread_mutex_lock(&mlock);
        old = total_balance;
        delay(100000);
        total_balance = old + 1;

        // thread_spin_unlock(&lock);
        thread_mutex_unlock(&mlock);
    }
  
    printf(1, "Done s:%s\n", b->name);

    thread_exit();
    return;
}

int main(int argc, char *argv[]) {

  struct balance b1 = {"b1", 3200};
  struct balance b2 = {"b2", 2800};
   
  void *s1, *s2;
  int t1, t2, r1, r2;

  // lock init
  // thread_spin_init(&lock);
  thread_mutex_init(&mlock);

  s1 = malloc(4096);
  s2 = malloc(4096);

  t1 = thread_create(do_work, (void*)&b1, s1);
  t2 = thread_create(do_work, (void*)&b2, s2); 

  r1 = thread_join();
  r2 = thread_join();
  
  printf(1, "Threads finished: (%d):%d, (%d):%d, shared balance:%d\n", 
      t1, r1, t2, r2, total_balance);

  exit();
}