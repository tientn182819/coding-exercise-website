#include <stdio.h> 
#include <unistd.h> 
#include <signal.h> 
#include <err.h> 
 
#define TIME_LIMIT 2 
 
void my_function(); 
void alarm_handler(int); 
 
int main() 
{ 
    if (sigaction(SIGALRM, NULL, NULL) == -1) 
        err(1, NULL); 
 
    // install an alarm handler for SIGALRM 
    signal(SIGALRM, alarm_handler); 
 
    // install an alarm to be fired after TIME_LIMIT 
    alarm(TIME_LIMIT); 
 
    // call your function 
    my_function(); 
 
    // cancel any previously set alarm 
    alarm(0); 
 
    return 0; 
} 
 
void my_function() 
{ 
    //sleep(1); 
    sleep(3); 
    printf("%s\n", "Returning from my_function."); 
} 
 
void alarm_handler(int sig) 
{ 
    printf("%s\n", "Seems you crossed time limit!"); 
} 