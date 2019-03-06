CC=g++
MAKE=make
LFLAGS=-shared -lpthread
CFLAGS=-Wall -fPIC
CLEAN=rm -f
PROGRAM_NAME=mail.so
DESTINATION_PATH=../../../bin/

MAIN_SRC_DIR=../../
EOBJ_PREFIX=../bin/obj

OBJECT_FILES=*.o
EOBJECT_FILES=../../../bin/obj/Message.o ../../../bin/obj/Mutex.o ../../../bin/obj/Config.o ../../../bin/obj/Log.o
SOURCE_FILES= mail.cpp MailThread.cpp

$(PROGRAM_NAME): $(OBJECT_FILES) $(EOBJECT_FILES)
	$(CC) $(LFLAGS) -o $@ $^
	cp $(PROGRAM_NAME) $(DESTINATION_PATH)

$(OBJECT_FILES): $(SOURCE_FILES)
	$(CC) -c $^
	
$(EOBJECT_FILES):
	$(MAKE) -C $(MAIN_SRC_DIR) $(EOBJ_PREFIX)/$(notdir $@)	

clean:
	$(CLEAN) *.o
	$(CLEAN) $(PROGRAM_NAME) 
	$(CLEAN) $(DESTINATION_PATH)$(PROGRAM_NAME) 
