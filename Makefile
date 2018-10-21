BUILD_DIR = /tmp/buildir

default: submission.zip
.PHONY: submission.zip
submission.zip:
	rm -rf ~/Desktop/submission.zip
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/src
	cp -r opencv src scripts/* $(BUILD_DIR)/src
	zip --symlinks -r -9 ~/Desktop/submission.zip $(BUILD_DIR)/src