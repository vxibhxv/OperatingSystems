My shell:

This is a simple shell I created using C language.
The shell itself is just an infinite loop which produces a prompt(&: ) to the user, accepts commands, parses it and carries out respective commands.
If the command entered is invalid an error message is produced to the user and they are asked to try again.
This only ends when the user enters the "exit" command.
Other than exit command I implemented 9 other commands in my shell. The commands are:

The commands described here are internal commands, i.e they are executed by the shell, exit is one of these commands.

1) Change directory (cd):
	This command is used to change the working directory of the program. To do this I used the chdir() function defined in C. The chdir() function takes the char* type argument of the directory to go to. This argument must however be in the current folder else an error would be produced.
	cd command must always have an argument, otherwise it is invalid.
	If the argument is / it goes to the home directory of the system
	If the argument is ~ it goes to the directory of the user.
	If the entered argument is an invalid directory chdir returns a non-zero value and then an error message is printed with a suggestion to the user.

2) Echo command (echo)
	This command is used to just print back onto the terminal the arguments passed. To do this printf() function was used.
	The argument passed along with the command is just printed back onto the terminal.
	If no argument is passed along with echo this just prints a blank and moves to the next line.
	There are two options that can be used along with this command.
	These options are:
		-n: Using this option removes the trailing \n and prints the argument and moves back to the shell without 
			moving to the next line. Only one argument can be used with this option.
		-E: Using this option ignores the \ characters in the argument passed and prints the remaining values.
			Only one argument can be used with this option.
	If there are too many arguments passed the remainder are ignored and only the first argument is printed back.

3) Print working directory (pwd)
	This command is used to print the working directory of the program. To do this I used the getcwd option in C.
	An argument is not required for this, and if arguments are entered they are just ignored and the command prints the working directory.
	If an error occurs while trying to access the working directory an appropriate error message is printed.

4) History command (history)
	This command is used to print the list of the commands entered in this session to the shell. I do this by using a file called cmds.txt and print them from the file when called.
	The shell stores all commands irrespective of whether or not they are invalid and prints them when required.
	Calling the history command on it's own would print the commands entered in the current session.
	There are two options I implemented with this command:
		-c: Using this clears the history. 
		-w: Using this command stores the commands into a file on the disk, clears whatever was there before and overwrites the value in the file stored on disk.
	If too many arguments are entered this returns a message to the user and does not print anything.

The next few commands are external commands, i.e an external file is executed to carry out the commands.
For all the external commands a fork system call is used to create a child process. In the child process the execv system call is used to call the appropriate function and pass all the arguments read in the shell to the function that called it.
If there was a failure in the execv system call, the shell prints failed and continues execution.
In the parent process created the shell waits for the child process and then continues execution.

5) Date command (date)
	This command is used to print the current time of the system. This is done by using a time type variable to read the time from the system, and using the localtime function or the gmtime function on the time variable, the values are stored into a tm type structure.
	The local time is printed by default.
	There are two options I implemented:
		-u: This prints the UTC time currently using the gmtime function.
		-I: This prints the current date
	If there are more arguments passed to the function, no evaluation happens and an error message is printed. 
	This function the returns back to the shell.

6) Cat command (cat)
	This command is used to print the contents of an entered file. Open and read system calls are used to do the same.
	This argument however always requires arguments to be passed to it.
	If no argument is passed an error message is printed and the program returns back without executing.
	There are two options I implemented with this:
		-n: This prints the line number along with each line in the file that has been opened.
		-e: This prints $ at the end of each line.
	If the argument passed is an incorrect file then this returns an error with the open command and an error message is printed. Once the error message has been printed the program stops execution and goes back to the shell.
	If too many arguments are passed this also causes an error, and a message is printed before returning back to the shell.

7) Make directory (mkdir)
	This command is used to create a new directory in the directory of the shell's execution. I used mkdir function on C for this command.
	This command also requires an argument along with it and if not entered this prints an error messages and returns back to the shell.
	Using the stat command I first check if the directory exists and if it doesn't then an error message is printed and the process returns backs to the shell.
	There are two options I implemented with this command:
		-p: This option is used to recursively create directories separated by /.
		-v: This option is the verbose option and prints the directories that have been created when they have been created.
	If stat returns -1 only then can the directory be created since no information was found.
	This then returns an error message if some information was found using stat.
	The access mode is defined in the mkdir function, on MacOS the widest possible access mode is through 0755 and therefore this is what I used in order to create my new directory.
	If too many arguments are passed this again causes an error and an error message is printed after which the process returns back to the shell.

8) Remove (rm)
	This command is used to remove a file passed as an argument provided this is not a directory.I used the remove function to do this.
	This command also requires an argument along with it and if not entered this prints an error message and returns back to the shell.
	Using the stat command I first check if the file entered exists. If it doesn't this prints an error messages and returns back to the shell. 
	I then check if the file passed is a directory and if it is, an error message is passed and the directory isn't deleted and it simply returns back to the shell.
	If no error is detected then the file is removed.
	There are two options you can use with this command:
		-i: This option asks for confirmation before deleting the entered file
		-v: The verbose option. This prints the deleted file once it has been deleted.
	If too many arguments are passed or an invalid command is passed an error message is printed after which the process stops executing and returns back to the shell.

9) List computer files (ls)
	This command returns a list of the files in the current directory. This argument does not take any arguments with it unless it's the options entered.
	If there are too many arguments entered this prints an error message, stops executing and returns back to the shell.
	This command by default sorts the files in ascending order alphabetically and prints the files.
	The options I implemented with this are:
		-a: This prints all the files in the current directory including the hidden files.
		-f: This prints the files not in a sorted manner. This command implicitly calls the -a option and prints all the hidden files too.

Sample commands you can run:
 1 ls 
 2 ls ab 
 3 cd Op 
 4 cd Open_CSV 
 5 ls 
 6 ls -f 
 7 cd .. 
 8 echo hello 
 9 echo -n hi 
 10 echo -e "Hello\tWorld" 
 11 echo -E "Hello\tWorld" 
 12 pwd 
 13 history -w 
 14 history 
 15 date 
 16 date -u 
 17 date -I 
 18 ls -a 
 19 cat date.c 
 20 cate -n date.c 
 21 cat -n date.c 
 22 cat -e date.c 
 23 mkdir -p Hi/Hello 
 24 ls 
 25 mkdir Hi 
 26 cat an 
 27 cd Hi 
 28 mkdir -v New_file 
 29 ls 
 30 mkdir New_file 
 31 ls 
 32 mkdir abc cde 
 33 ls 
 34 cd .. 
 35 ls 
 36 rm -v car.class 
 37 rm -i wheels.class 
 38 rm Hi 
 39 history 
 40 history -c
 41 exit


