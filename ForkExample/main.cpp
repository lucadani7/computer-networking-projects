#include <iostream>
#include <unistd.h>

using namespace std;

void die(const char *messageError) {
    perror(messageError);
    exit(1);
}

int main() {
    pid_t pid;
    int rv;
    switch (pid = fork()) {
        case -1:
            die("Fork");
        case 0:
            printf(" PC: Proces copil!\n");
            printf(" PC: Am PID-ul %d\n", getpid());
            printf(" PC: PID-ul parintelui este %d\n", getppid());
            printf(" PC: Da-mi un status de iesire: ");
            scanf(" %d", &rv);
            printf(" PC: Am plecat!\n");
            exit(rv);
        default:
            printf(" PP: Proces parinte!\n");
            printf(" PP: Am PID-ul %d\n", getpid());
            printf(" PP: Am copil cu pidul %d\n", pid);
            printf(" PP: Astept ca PC sa apeleze exit()...\n");
            wait(&rv);
            printf(" PP: Statusul de iesire al PC este: %d\n", WEXITSTATUS(rv));
            printf(" PP: Am plecat!\n");
    }
}
