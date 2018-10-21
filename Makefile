BUILD_DIR = /tmp/buildir

default: submission.zip
.PHONY: submission.zip
submission.zip:
	rm -rf ~/Desktop/submission.zip
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/src
	cp -r opencv src CMakeLists.txt scripts/* $(BUILD_DIR)/src
	cd $(BUILD_DIR) && zip --symlinks -r -9 ~/Desktop/submission.zip src