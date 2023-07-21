#include <iostream>
#include <unistd.h>

using namespace std;

void die(const char* errorMessage) {
    perror(errorMessage);
    exit(1);
}

int main() {
    pid_t pid; // PID-ul procesului copil
    int status; // starea de terminare a procesului copil
    printf("Vom executa comanda...\n");
    if ((pid = fork()) < 0) {
        die("Fork()");
    } else if (pid) {
        if (wait(&status) < 0) {
            perror("Wait()");
        }
        printf("Comanda a fost executata.\n");
        exit(0);
    } else {
        execlp("ls", "ls", "-a", "-l", nullptr);
        die("Eroare de executie!\n");  // daca ajungem aici, inseamna ca nu s-a putut executa
    }
}
