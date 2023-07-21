#include <iostream>
#include <unistd.h>

using namespace std;

void die(const char* errorMessage) {
    perror(errorMessage);
    exit(1);
}

void sighandler(int sign) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        die("fork()");
    } else if (!pid) {
        execl("/usr/bin/less", "less", "/etc/services", nullptr);
        die("exec()");
    } else {
        if (wait(nullptr) < 0) {
            perror("wait()");
        }
    }
}

int main() {
    bool conditie = signal(SIGUSR2, sighandler) == SIG_ERR;
    if (conditie) {
        die("signal()");
    }
    pause();
    return 0;
}
