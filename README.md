# ProducerConsumerCPP

// PROBLEM:
//  - Producer will produce and consumer will consume with synchronisation
//     of common buffer.
//  - Will continue intil producer thread does not produce any data for the consumer
//  - Threads will use a condition variable to notify each other
//  - Mutex needs to be used because the CV waits on the Mutex
