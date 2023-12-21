## sms_simulation

# SMS Simulation Exercise

The objective is to simulate sending a large number of SMS alerts, like for an emergency alert service.
The simulation consists of three parts:
1. A producer that generates a configurable number of messages (default 1000) to random phone
numbers. Each message contains up to 100 random characters.
2. A configurable number of senders who pick up messages from the producer and simulate
sending messages by waiting a random period of time distributed around a configurable mean.
Senders also have a configurable failure rate.
3. A progress monitor that displays the following and updates it every N seconds (configurable):
a. Number of messages sent so far
b. Number of messages failed so far
c. Average time per message so far

One instance each for the producer and the progress monitor will be started while a variable number of
senders can be started with different mean processing time and error rate settings.

# Solution:

How to Run:

Download the zip file and extract its contents on an Ubuntu 32-bit system.
Open a terminal and navigate to the directory where the files are located.
Type 'make' in the command line to compile the code, followed by './sms_exec' to run the program.

Explanation of the Code:

I've implemented the code using the pthread library, creating three types of threads: producer_thread, sender_threads, and progress_thread.
The producer_thread is responsible for simulating the generation of messages.
sender_threads simulate the sending of messages, considering send times and error rates.
The progress_thread keeps track of the messages successfully sent and failed, and it displays this information.

Main Function:

In the main function, the user is given the flexibility to specify the number of sender threads, each with its own mean processing time and error rate.

Concurrency Management:

To ensure data integrity, I have employed a mutex lock called progress_lock to protect the shared variables: messages_sent, messages_failed, and total_send_time.

Output:

Please find below the output generated when running the program in the Ubuntu 32-bit terminal:

![ouput_img](https://github.com/kas140472/sms_simulation/blob/main/ss1.png)
