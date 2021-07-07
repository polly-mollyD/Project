# Producer-consumer problem
The code is implemented in C programming language using process semaphores and a thread mutex.

## Problem description
The producer-consumer problem defines several processes, the producer and the consumer, who share the buffer of fixed-size N. The producer's task is to generate the item and insert it to the empty slot in the buffer. And at the same time checks whether the buffer is full. Then continues to execute the same process again. At the same time, the consumer waits for data and, when the producer puts the data, takes it from the buffer. It suspends the process when the buffer is empty. The problem is to make sure that the producer will not try to add an item into the buffer if it is full and that the consumer will not try to remove data from an empty buffer.

## Implementation
In my program, each producer and consumer are implemented as a separated thread. The number of each of them is specified in the #define directive. Each thread operates in an infinite loop.
The producer randomly generates an item (integer from 0 to 100), sleep for 1 sec, then puts this number to the buffer and prints "Producer #n (producer number) inserts (item)". 
The buffer is implemented as a FIFO circular array and have a constant number of slots. 
The consumer takes this item from the buffer, prints "Consumer #n (consumer number) takes (item)" and then sleeps. I am using semaphores for counting empty "sem_empty" and full "sem_full" slots and a mutex lock is used to represent 'mutex'.If the buffer is empty, the consumer thread will block until there is at least one item in the buffer at which point it will be woken up.

## Expected result
```
Producer 1 inserts 73

Producer 3 inserts 32

Producer 2 inserts 27

Consumer 2 takes 27

Consumer 3 takes 32

Consumer 1 takes 73

Producer 2 inserts 90

Producer 3 inserts 83

Consumer 2 takes 83

Consumer 3 takes 90

Producer 1 inserts 5

Consumer 1 takes 5

```
