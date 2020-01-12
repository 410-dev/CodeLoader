#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
--------------------------------------------------------------
Library Structure

/Library/CodeLoader         (Root Library)
/Library/CodeLoader/bin     (Binaries)
/Library/CodeLoader/bundles (Loaded bundles, bundle extension is: .boot.loaderb)
/Library/CodeLoader/cache   (Cache Directory)
/Library/CodeLoader/conf    (Configurations)
/Library/CodeLoader/info    (Information such as trusted and trusted hosts)
/Library/CodeLoader/src     (Source codes)
--------------------------------------------------------------
Bundle Structure

./codesign               (Bundle code signature)
./exec                   (Runnable binary / shell)
./                       (Other resources)
--------------------------------------------------------------
*/

// Exit Status Flags
const char* operationIncomplete = "/tmp/CodeLoader.Loop.operationIncomplete";
const char* safeStart = "/Library/CodeLoader/conf/boot/safeboot_loop";

// Variables
int exitCode = 0;

// Read Last Exit Status
void status() {
	printf("Reading last exit status...\n");
	if( access(safeStart, F_OK) != -1 ) {
	    exitCode = 1;
	} else if( access(operationIncomplete, F_OK) != -1) {
		exitCode = 2;
	} else {
		exitCode = 0;
	}
}

int main() {
	status();
	if (exitCode == 0) {
		exitCode = system("/Library/CodeLoader/bin/exec_codeloader-loop");
	}
	if (exitCode == 0) {
		printf("Operation Success.\n");
		system("echo \"I:BOOT_EXIT=CLEAN\" >> /tmp/CodeLoader.Boot.Report");
	}else if (exitCode == 1) {
		printf("Safemode is enabled.\n");
		system("echo \"E:LOOP_EXIT=SAFEMODE\" >> /tmp/CodeLoader.Loop.Report");
	}else if (exitCode == 2) {
		printf("Operation did not cleanly finished.\n");
		system("echo \"E:LOOP_EXIT=UNCLEAN_FINISH\" >> /tmp/CodeLoader.Loop.Report");
	}
	exitCode = 0;
	return exitCode;
}
