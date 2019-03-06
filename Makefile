OUTPUT_DIR=./bin
.PHONY : clean all install

all: core scanlog scanprocess dummy xmpp mail

core:
	make -C ./src

#monitoring plugins
scanlog: 
	make -C ./src/MonitoringPlugins/ScanLog
scanprocess:
	make -C ./src/MonitoringPlugins/ScanProcess

#notify plugins
dummy:
	make -C ./src/NotifyPlugins/Dummy 
xmpp:
	make -C ./src/NotifyPlugins/XMPP
mail:
	make -C ./src/NotifyPlugins/Mail	

install:
	cp $(OUTPUT_DIR)/*.so /usr/lib
	cp ./mind.conf /etc/ -i
	cp $(OUTPUT_DIR)/start /bin/mind
	
clean:
	make -C ./src clean
	make -C ./src/NotifyPlugins/Dummy clean
	make -C ./src/NotifyPlugins/XMPP clean
	make -C ./src/MonitoringPlugins/ScanLog clean
	make -C ./src/NotifyPlugins/Mail clean
