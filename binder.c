#include <linux/input.h>
#include <weston.h>
#include <unistd.h>
#include <fcntl.h>

static void
execvp_suppressed(const char *file, char *const argv[])
{
	int pid = fork();

	if (pid)
		return;

	int fd = open("/dev/null", O_WRONLY);

	dup2(fd, 1);
	dup2(fd, 2);

	close(fd);

	execvp(file, argv);
}

static void
binder_callback_alt(struct weston_keyboard *keyboard, unsigned int time, uint32_t key,
		void *data)
{
	switch (key) {

	/* MPD controls */
	case KEY_8:
		execvp_suppressed("mpc", (char * const[]) {"mpc", "prev", NULL});
		break;
	case KEY_9:
		execvp_suppressed("mpc", (char * const[]) {"mpc", "next", NULL});
		break;
	case KEY_0:
		execvp_suppressed("mpc", (char * const[]) {"mpc", "toggle", NULL});
		break;

	/* Backlight controls */
	case KEY_F5:
		execvp_suppressed("sudo", (char * const[]) {"sudo", "sh", "-c",
				"echo 15 > /sys/class/backlight/intel_backlight/brightness", NULL});
		break;
	case KEY_F6:
		execvp_suppressed("sudo", (char * const[]) {"sudo", "sh", "-c",
				"echo 900 > /sys/class/backlight/intel_backlight/brightness", NULL});
		break;

	}
}

static void
binder_callback_ctrl_alt(struct weston_keyboard *keyboard, unsigned int time, uint32_t key,
		void *data)
{
	switch (key) {

	/* Open a terminal */
	case KEY_T:
		execvp_suppressed("xfce4-terminal", (char * const[]) {"xfce4-terminal", NULL});
		break;

	}
}

static void
binder_add_bindings(struct weston_compositor *ec)
{
	weston_compositor_add_key_binding(ec, KEY_8, MODIFIER_ALT, binder_callback_alt, NULL);
	weston_compositor_add_key_binding(ec, KEY_9, MODIFIER_ALT, binder_callback_alt, NULL);
	weston_compositor_add_key_binding(ec, KEY_0, MODIFIER_ALT, binder_callback_alt, NULL);
	weston_compositor_add_key_binding(ec, KEY_F5, MODIFIER_ALT, binder_callback_alt, NULL);
	weston_compositor_add_key_binding(ec, KEY_F6, MODIFIER_ALT, binder_callback_alt, NULL);
	weston_compositor_add_key_binding(ec, KEY_T, MODIFIER_CTRL | MODIFIER_ALT, binder_callback_ctrl_alt, NULL);
}

WL_EXPORT int
wet_module_init(struct weston_compositor *ec, int *argc, char *argv[])
{
	weston_log("Keybinder plugin activated, keybinds:\n");
	weston_log("  ALT+8: mpc prev\n");
	weston_log("  ALT+9: mpc next\n");
	weston_log("  ALT+0: mpc toggle\n");
	weston_log("  ALT+F5: sudo sh -c 'echo 15 > /sys/class/backlight/intel_backlight/brightness'\n");
	weston_log("  ALT+F6: sudo sh -c 'echo 900 > /sys/class/backlight/intel_backlight/brightness'\n");
	weston_log("  CTRL+ALT+T: xfce4-terminal\n");
	binder_add_bindings(ec);
}
