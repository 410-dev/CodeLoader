# CodeLoader
 Powerful Code Loading Platform for macOS

------------------------

## What is this?

- This software loads series of codes when system starts up.

## How do I use it?

- First you should install through Macintosh Packager, or manually place file and register the launch daemons to launchd.
- Once you've done it, place the bundle that has correct structure into /Library/CodeLoader/bundles/.
  - The extension .boot.loaderb will load only once after boot. Rebooting will run the code again.
  - The extension .loop.loaderb will keep run after boot.

## Security Problem?

- The code will run under superuser permission. 
- The launcher WILL NOT check the virus or signature of the binary inside the bundle.
- Therefore you MUST install the bundles that is provided from trusted source.

## The script does not run!

- Make sure you have correct format of bundle including exec, extension, paths, etc.

- Try removing conflicting bundles.

- Check whether safe mode is enabled.

  - You can check the file: /Library/CodeLoader/conf/boot/safeboot
    - If the file exists, then the safe mode is enabled.
    - Otherwise, the safe mode is off.

- Check the launchctl.

  - Run "sudo launchctl list | grep codeloader".

- If none of this works, contact to nginx410.s@gmail.com.

  