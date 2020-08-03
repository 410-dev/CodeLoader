#!/bin/bash
source "$(dirname "$0")/conf"
source "$(dirname "$0")/global_fnc"
log "======Start of Log======"
if [[ ! -d "$container_path" ]]; then
	mkdir -p "$container_path"
	if [[ $? -ne 0 ]]; then
		log "[-] EUID is not zero, unable to repair container."
		exit 64
	fi
fi

if [[ -f "$enter_safemode" ]]; then
	log "[-] Safe mode is enabled, therefore unable to continue."
	exit 60
fi

log "[*] CodeLoader started."
if [[ "$allow_load" == "YES" ]] && [[ ! -f "$launch_done_flag" ]]; then
	ls -1 "$container_path" | while read module
	do
		chmod +x "$container_path/$module"
		xattr -xc "$container_path/$module"
	done
	if [[ "$allow_data_sourcing" == "YES" ]]; then
		log "[*] CodeLoader is copying memory data..."
		chmod +x "$(dirname "$0")/getsrc"
		source "$(dirname "$0")/getsrc"
	else
		log "[*] Loading memory data is disabled."
	fi

	log "[*] CodeLoader is loading extensions..."

	if [[ "$allow_async_extension" == "YES" ]]; then
		log "[*] Loading asynchromodules..."
		chmod +x "$(dirname "$0")/asynchromodule"
		"$(dirname "$0")/asynchromodule"
	else
		log "[*] Loading asynchromodules is disabled."
	fi
	
	touch "$launch_done_flag"
fi
log "======End of Log======"
exit 0