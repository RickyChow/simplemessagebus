all: messagebus

clean:
	rm -f *.o messagebus

messagebus: main.cpp messagebus2.h messagebus.h eventmessagedef.h
	g++ main.cpp -o messagebus
