all: messagebus

clean:
	rm -f *.o messagebus

messagebus: main.cpp messagebus.h eventmessagedef.h
	g++ main.cpp -o messagebus
