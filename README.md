# sms_simulation

SMS Simulation Exercise

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
