**5. What is a signal? How can it be handled (describe three possible responses to a signal)? Where do signals come from (identify three sources)?**



\-> A signal is some sort of interruption of the process that is being run or exec.

\-> 3 possible responses to a signal would be Catch, Ignore, or Default Action

So what it means is that:



\-> Catch (Handle the signal):

&#x09;The process executes a user-defined function known as the signal handler or trap, specifically to manage the incoming signal



\-> Ignore:

&#x09;The process explicitly instructs the kernel to ignore the signal, preventing it from having any effect.



\-> Default Action:

&#x09;The process allows the OS to perform its default action. Depending on the signal, this usually involves terminating the process, ignoring the signal or suspending the signal



\-> 3 sources where the  signal comes from:



\-> Users via Terminal:

&#x09;User interaction with a terminal, such as pressing Ctrl + C (generates SIGINT to interrupt) or Ctrl + Z (generates SIGTSTP to suspend)



\-> The Operation System/Kernel:

&#x09;OS generates signal when a process  commits a prohibited action such as accessing memory outside its allocated space (SIGEGV) or dividing by zero (SIGFPE)



\-> Other Processes:

&#x09;A process can send signals to other processes using the kill command or system call to send commands such as terminate (SIGKILL) or hang uup (SIGHUP)



**6. How does a process send a signal to another process? Provide three examples using different signals.**



A process sends a signal to another prcess by using the kernel as a mediator. The sending process typically identifies the recipient by its process ID  (PID) a invokes a system call



Example:

\-> SIGTERM (request termination politely) \[number 15]

&#x09;target process can catch this and clean up before exiting

\-> SIGUSR1 (send a user-defined signal) \[number 10]

&#x09;reserved for application-defined purposes.

\-> SIGKILL (forcefully terminate a process) \[number 9]

&#x09;cant be caught, blocked, or ignored. The kernel terminates the process immediately. This is a last resort when a process is unresponsive.

