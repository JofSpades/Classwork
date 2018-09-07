all: mutex_test barrier_test worker1_test worker2_test alternating_test rwlock_test

CFLAGS=-Wno-deprecated-declarations -g -Wall

mutex_test: mutex.c mutex_test.c mutex.h test.h
	gcc $(CFLAGS) --std=gnu99 mutex.c mutex_test.c -o mutex_test -lpthread

barrier_test: barrier.c barrier_test.c mutex.c barrier.h test.h
	gcc $(CFLAGS) --std=gnu99 barrier.c mutex.c barrier_test.c -o barrier_test -lpthread

worker1_test: worker1.c worker1_test.c test.h
	gcc $(CFLAGS) --std=gnu99 worker1.c worker1_test.c -o worker1_test -lpthread

worker2_test: worker2.c worker2_test.c test.h barrier.c
	gcc $(CFLAGS) --std=gnu99 worker2.c worker2_test.c -o worker2_test -lpthread 

alternating_test: alternating.c alternating_test.c test.h barrier.c
	gcc $(CFLAGS) --std=gnu99 alternating.c alternating_test.c -o alternating_test -lpthread barrier.c

rwlock_test: rwlock_test.c rwlock.c rwlock.h test.h
	gcc $(CFLAGS) --std=gnu99 rwlock.c rwlock_test.c -o rwlock_test -lpthread


test: mutex_test barrier_test rwlock_test worker1_test worker2_test 
	@./mutex_test
	@./barrier_test
	@./rwlock_test
	@./worker1_test
	@./worker2_test

clean:
	rm -f *~ mutex_test barrier_test worker1_test worker2_test alternating_test rwlock_test
