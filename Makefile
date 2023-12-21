#
# This is the Makefile that can be used to create the "sms_exec" executable
# To create "sms_exec" executable, do:
#	make
#

sms_exec: sms.c
	gcc -g -Wall -o sms_exec sms.c -pthread -lm

clean:
	rm -f *.o sms_exec

