weston-binder
=============

This is a module for weston (makes sense with the desktop shell) for parsing
keybindings from weston.ini.


Building
--------
The build system is a simple one. To create the weston module, binder.so:

	make

To install it:

	make install

Usage
-----
To use this module, add its binder.so to the modules option:

	[core]
	modules=binder.so

For each key you want bound, append a similar keybind option to your
weston.ini:

	[keybind]
	key=ctrl+alt+t
	exec=weston-terminal

Note that the key is bound before everything in the [keyboard] section is
applied, so if your logical layout is different from your physical one, your
configuration is going to be going to have to reflect your unaltered physical
keyboard layout (e.g. in Dvorak use `ctrl+alt+k` for the above example).

The `exec` string is fed to `sh -c {}`, so you can also put more complicated
lines in:

	[keybind]
	key=alt+f6
	exec=sudo sh -c 'echo 900 > /sys/class/backlight/intel_backlight/brightness'

Using parentheses around the command seems to be necessary if the command
starts with an environment variable.

The case insensitive `key` parameter should be simple enough to get right. Join
different modifiers and keys with a plus sign. If you get it wrong, the module
reflects on your failure in weston logs.

To find the names of obscure keys, see linux/input-event-codes.h (probably in
/usr/include/). The "KEY_" prefix must be omitted in the configuration file.

There's a total of 3 modifiers you can have: ctrl, alt and super.

Examples
--------
Here's a few useful examples:

	# PulseAudio sound controls
	[keybind]
	key=mute
	exec=pamixer -t

	[keybind]
	key=volumeup
	exec=pamixer -i 10

	[keybind]
	key=volumedown
	exec=pamixer -d 10

	# Music Player Daemon controls
	[keybind]
	key=alt+8
	exec=mpc prev

	[keybind]
	key=alt+9
	exec=mpc next

	[keybind]
	key=alt+0
	exec=mpc toggle

