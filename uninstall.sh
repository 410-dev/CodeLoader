#!/bin/bash
echo "1/2: Removing Library..."
sudo rm -rf "/Library/CodeLoader"
echo "2/2: Unloading from launchctl..."
sudo launchctl unload -w "/Library/LaunchDaemons/me.410.codeloader.plist"
sudo rm -f "/Library/LaunchDaemons/me.410.codeloader.plist"