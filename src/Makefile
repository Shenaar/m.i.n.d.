CC=g++
LFLAGS=-Wall -lpthread -ldl -L.
CLEAN=rm -f
PROGRAM_NAME=start

OUTPUT_DIR=../bin
OBJ_DIR=../bin/obj
SOURCE_FILES=main.cpp Thread.cpp Overseer.cpp Mutex.cpp Config.cpp Library.cpp Message.cpp Log.cpp Daemon.cpp MessageGenerator.cpp MessageDispatcher.cpp NoticePlugin.cpp MonitoringPlugins.cpp
OBJ_FILES=$(SOURCE_FILES:%.cpp=$(OBJ_DIR)/%.o)


$(OUTPUT_DIR)/$(PROGRAM_NAME): $(OBJ_FILES)
	$(CC) $(LFLAGS) $^ -o $@ 
	
$(OBJ_DIR)/%.o : %.cpp
	$(CC) -c $< -o $@

clean:
	$(CLEAN) $(OBJ_DIR)/*.o
	$(CLEAN) $(OUTPUT_DIR)/$(PROGRAM_NAME)	
