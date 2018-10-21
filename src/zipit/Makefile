BINARY_FILE = "../cmake-build-release/not_ai"

default: ai.zip
	cp ai.zip ~/Desktop

ai.zip: src src/build.sh src/run.sh src/prog
	zip -r ai.zip src

src:
	mkdir src

src/prog:
	cp $(BINARY_FILE) ./src/prog

src/build.sh:
	cp ./build.sh ./src/build.sh

src/run.sh:
	cp ./run.sh ./src/run.sh

clean:
	rm -rf src ai.zip
 
