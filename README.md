# CodeLoader
 Powerful Code Loading Platform for macOS

------------------------

## What is this?

- This software loads series of codes when system starts up.

## How do I use it?

- Install it with "install" file included in releases. Then place the scripts that has correct structure to /Library/CodeLoader/modules_container/.
  - The extension .moddt will not be executed, but will provide environment variable.
  - The extension .clasmod will be executed once, asynchronously on boot.

## Security Problem?

- The code will run under superuser permission. 
- The launcher WILL NOT check the virus or signature of the script.
- Therefore you MUST install the scripts that is provided from trusted source.

## The script is not running!

- Make sure you have correct script.
- Try removing conflicting script.
- Check the launchctl.

  - Run "sudo launchctl list | grep codeloader".
- Check configuration.
  - Open /Library/CodeLoader/bin/conf with a text editor (vim, nano, etc.)
  - Check whether these options are set to NO. If so, change them to YES.
    - allow_async_extension
    - allow_data_sourcing
      - This can be turned off, but since variables are not provided, the scripts may not function properly.
    - allow_load

- If none of this works, contact to nginx410.s@gmail.com.

  