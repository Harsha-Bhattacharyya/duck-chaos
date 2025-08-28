#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define DUCK_VIDEO   "/usr/share/duck-chaos/duck.mp4"
#define DUCK_AUDIO   "/usr/share/duck-chaos/lavendertown.mp3"
#define DUCK_IMAGE   "/usr/share/duck-chaos/duck.jpeg"

void play_duck_video(const char *file) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "command -v mpv >/dev/null 2>&1 && mpv --loop '%s' &", file);
    if (system(cmd) == 0) return;

    snprintf(cmd, sizeof(cmd), "command -v vlc >/dev/null 2>&1 && vlc --loop '%s' &", file);
    if (system(cmd) == 0) return;

    snprintf(cmd, sizeof(cmd), "command -v xdg-open >/dev/null 2>&1 && xdg-open '%s' &", file);
    if (system(cmd) == 0) return;

    fprintf(stderr, "⚠️ No video player found (mpv/vlc/xdg-open). Skipping duck video.\n");
}

void open_new_terminal(const char *cmd) {
    const char *terminals[] = {
        "gnome-terminal -- bash -c \"%s; exec bash\"",
        "konsole -e bash -c \"%s; exec bash\"",
        "xfce4-terminal -e bash -c \"%s; exec bash\"",
        "lxterminal -e bash -c \"%s; exec bash\"",
        "terminator -x bash -c \"%s; exec bash\"",
        "xterm -e bash -c \"%s; exec bash\"",
        "kitty bash -c \"%s; exec bash\"",
        "alacritty -e bash -c \"%s; exec bash\""
    };

    int nterms = sizeof(terminals)/sizeof(terminals[0]);
    char command[512];
    for(int i = 0; i < nterms; ++i) {
        snprintf(command, sizeof(command), terminals[i], cmd);
        if(system(command) == 0)
            return;
    }
}

// Copy a file from src to dst, returning 0 on success
int copy_file(const char *src, const char *dst) {
    FILE *in = fopen(src, "rb");
    if (!in) return -1;
    FILE *out = fopen(dst, "wb");
    if (!out) {
        fclose(in);
        return -1;
    }

    char buf[8192];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) {
            fclose(in);
            fclose(out);
            return -1;
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}

void flood_pictures_directory() {
    const char *pictures_dir = "/home/";
    const char *user = getenv("USER");
    static char path[512];
    if(user == NULL) {
        return;
    }
    snprintf(path, sizeof(path), "/home/%s/Pictures", user);

    // Create ~/Pictures if not exists
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if(mkdir(path, 0700) == -1) {
            return;
        }
    }

    char src_path[] = DUCK_IMAGE;
    char dst_path[1024];

    for (int i = 1; i <= 100; ++i) {
        snprintf(dst_path, sizeof(dst_path), "%s/duck%d.jpeg", path, i);
        if (copy_file(src_path, dst_path) != 0) {
        }
    }
}

int main() {
    printf("🦆 Duck Chaos Activated 🦆\n");

    for(int i = 0; i < 50; i++) {
        printf("DUCK %d 🦆\n", i + 1);
        fflush(stdout);
        usleep(100000);
    }

    play_duck_video(DUCK_VIDEO);
	play_duck_video(DUCK_AUDIO);
    for(int i = 0; i < 10; i++) {
        open_new_terminal("echo '🦆 A wild duck appears! 🦆'; while true; do echo QUACK; sleep 1; done");
        usleep(300000);
    }

    // Flood ~/Pictures with 100 duck jpeg images
    flood_pictures_directory();

    sleep(5);
    fprintf(stderr, "\n SYSTEM FAILURE: Kernel panic - not syncing: Duck invasion detected!\n");
    fprintf(stderr, "CPU: 0 PID: %d Comm: duck-simulator 🦆\n", getpid());
    fprintf(stderr, "Call Trace: [<deadduck>] quack_overflow+0x1f/0x42 🦆\n");
    fprintf(stderr, "--- End Kernel Panic 🦆 ---\n");

    while(1) {}

    return 0;
}

