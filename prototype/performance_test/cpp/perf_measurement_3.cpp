#include <stdio.h>
#include <stdlib.h>
#include <algorithm>   
#include <unistd.h> 
#include <signal.h> 
#include <err.h> 
#include <sys/resource.h> 
#include <sys/wait.h> 
#include <cstring>
#include <fcntl.h>



void my_function() 
{ 
    //sleep(1); 
    sleep(3); 
    printf("%s\n", "Returning from my_function."); 
} 
 

int get_memory_usage(pid_t pid) { 
    int NAME_MAX = 100;
    int fd, data, stack; 
    char buf[4096], status_child[NAME_MAX]; 
    char *vm; 
 
    sprintf(status_child, "/proc/%d/status", pid); 
    if ((fd = open(status_child, O_RDONLY)) < 0) 
        return -1; 
 
    read(fd, buf, 4095); 
    buf[4095] = '\0'; 
    close(fd); 
 
    data = stack = 0; 
 
    vm = strstr(buf, "VmData:"); 
    if (vm) { 
        sscanf(vm, "%*s %d", &data); 
    } 
    vm = strstr(buf, "VmStk:"); 
    if (vm) { 
        sscanf(vm, "%*s %d", &stack); 
    } 
 
    return data + stack;     
}

void signal_handler(int sig) 
{ 
    printf("%s\n", "Seems you crossed time limit!"); 
} 

// struct rlimit { 
//     rlim_t rlim_cur;  /* Soft limit */ 
//     rlim_t rlim_max;  /* Hard limit (ceiling for rlim_cur) */ 
// };

int main() { 
 
    struct sigaction sigact; 
    sigact.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT; 
    // define your own signal_handler 
    sigact.sa_handler = signal_handler; 
     
    if (sigaction(SIGALRM, &sigact, NULL) == -1) { 
        return -1; 
    } else if (sigaction(SIGXCPU, &sigact, NULL) == -1) { 
        return -1; 
    } 
 
    int pid; 
    // fork tạo ra một process mới
    if ((pid = fork()) == -1) { 
        perror("fork"); 
        exit(EXIT_FAILURE); 
    } else if (pid == 0) {    /* child */ 
 
        /* set resource limit values such as RLIMIT_CPU,  
         * RLIMIT_STACK, RLIMIT_RSS, etc. 
         * See `man setrlimit`. 
         */ 
 
        // exec user program 
 
    }  else {            /* parent */ 
 
        struct rusage resource_usage; 
        // set arbitrary lower limit value of memory used 
        int memory_used = 128; 
        pid_t pid2; 

        int memory_limit = 128;
        int status;
 
        do { 
            memory_used = std::max(memory_used, get_memory_usage(pid)); 
            if ((memory_used > memory_limit)){
            // Terminate the process 
                kill(pid, SIGKILL); 
            }
 
           // wait for the child process to change state 
            pid2 = wait4(pid, &status, WUNTRACED | WCONTINUED, &resource_usage); 
        } while (pid2 == 0); 
    }
 
} 

