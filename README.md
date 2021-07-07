# Producer-consumer problem
The code is implemented in C programming language using process semaphores and a thread mutex.

## Problem description
The producer-consumer problem defines several processes, the producer and the consumer, who share the buffer of fixed-size N. The producer task is to generate the item and insert it to the empty slot in the buffer. And at the same time checks if the buffer is full or not. Then continue same process again. At the same time, consumer waits for data and takes it from the buffer. It suspends the process when the buffer is empty. The problem is to make sure that the producer will not try to add item into the buffer if it is full and that the consumer will not try to remove data from an empty buffer.

## Implementation
Im my program, each producer and consumer are implemented as a separated thread. The number of each of them is specified in the #define directive. Each thread operates in an infinite loop. 
The producer randomly generates an item (integer from 0 to 100), sleep for 1 sec, then puts this number to the buffer and prints "Producer #n (producer number) inserts (item)". 
The buffer is to be implemented as a FIFO circular array and have a constant number of slots. 
The consumer takes this item from the buffer, prints "Consumer #n (consumer number) takes (item)" and then sleeps. I am using semaphores for counting empty "sem_empty" and full "sem_full" slots and a mutex lock is used to represent 'mutex'.If the buffer is empty, the consumer thread will block until there is at least one item in the buffer at which point it will be woken up.

## Getting Started
## Expected result
Producer 2 inserts 41

$ Producer 1 inserts 41

$ Producer 3 inserts 41

$ Consumer 1 takes 41

Consumer 2 takes 41

Consumer 3 takes 41

Producer 1 inserts 24

Producer 2 inserts 32

Consumer 1 takes 32

Producer 3 inserts 0

Consumer 2 takes 0

Consumer 3 takes 24
 
Producer 1 inserts 54

Producer 2 inserts 43

Consumer 3 takes 43

Consumer 1 takes 54

Producer 3 inserts 77

Consumer 2 takes 77

Producer 1 inserts 95

Producer 2 inserts 91

Consumer 1 takes 91

Producer 3 inserts 64

Consumer 3 takes 64
