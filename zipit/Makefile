BINARY_FILE = "../cmake-build-release/not_ai"

default: ai.zip
	cp ai.zip ~/Desktop

ai.zip: build.sh run.sh prog
	zip ai.zip ./build.sh ./run.sh ./prog

prog:
	cp $(BINARY_FILE) ./prog

clean:
	rm -f *.zip prog
 
