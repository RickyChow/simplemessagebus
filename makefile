all: messagebus

clean:
	rm -f *.o messagebus

messagebus: \
main.cpp \
globalmessagebus.cpp \
globalmessagebus.h \
eventmessagedef.h \
messagebus.h 
	g++ main.cpp globalmessagebus.cpp -o messagebus.exe
