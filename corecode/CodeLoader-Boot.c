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
const char* operationIncomplete = "/tmp/CodeLoader.Boot.operationIncomplete";
const char* operationComplete = "/tmp/CodeLoader.Boot.operationComplete";
const char* safeStart = "/Library/CodeLoader/conf/boot/safeboot";

// Variables
int exitCode = 0;

// Read Last Exit Status
void status() {
	printf("Reading last exit status...\n");
	if( access(safeStart, F_OK) != -1 ) {
	    exitCode = 1;
	} else if( access(operationIncomplete, F_OK) != -1 ) {
		exitCode = 3;
	} else if( access(operationComplete, F_OK) != -1) {
		exitCode = 2;
	} else {
		exitCode = 0;
	}
}

// Start Code
int main() {
	status();
	if (exitCode == 0) {
		exitCode = system("/Library/CodeLoader/bin/exec_codeloader-boot");
	}
	if (exitCode == 0) {
		printf("Operation Success.\n");
		system("echo \"I:BOOT_EXIT=0\" >> /tmp/CodeLoader.Boot.Report");
	}else if (exitCode == 1) {
		printf("Safemode is enabled.\n");
		system("echo \"E:BOOT_EXIT=1\" >> /tmp/CodeLoader.Boot.Report");
	}else if (exitCode == 2) {
		printf("Operation already finished.\n");
	}else if (exitCode == 3) {
		printf("Operation did not cleanly finished.\n");
		system("echo \"E:BOOT_EXIT=3\" >> /tmp/CodeLoader.Boot.Report");
	}
	exitCode = 0;
	return exitCode;
}
