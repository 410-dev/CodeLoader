#!/bin/bash
if [[ -f "/Library/CodeLoader/bin/init" ]]; then
	echo "Running update mode..."
	rm -rf "/Library/CodeLoader/bin"
fi
export username="$(whoami)"
echo "1/4: Copying Library..."
sudo cp -r "$(dirname "$0")/CodeLoader" "/Library"
echo "2/4: Adding launch daemon..."
sudo cp "/Library/CodeLoader/bin/me.410.codeloader.plist" "/Library/LaunchDaemons"
echo "3/4: Loading to launchctl..."
sudo launchctl load -w "/Library/LaunchDaemons/me.410.codeloader.plist"
echo "4/4: Setting up user..."
if [[ ! -f "/Library/CodeLoader/module_container/username.moddt" ]]; then
	if [[ "$username" == "root" ]]; then
		echo "Username cannot be root."
		echo -n "Please enter your username (/Users/[this]): "
		read username
		sudo echo "$username" > "/Library/CodeLoader/module_container/username.moddt"
	else
		sudo echo "$username" > "/Library/CodeLoader/module_container/username.moddt"
	fi
fi
