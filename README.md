# New-Unix-Shell

## Shell Manual

The commands you can utilize with this shell and their functionalities are listed below.

When you first start the shell, the shell environment will contain shell=<pathname>/myshell
where <pathname>/myshell is the full path for the shell executable (the one from which it was executed).

#### cd <directory> - change directory
**Description**
<br />
Changes the current default directory to <directory>. If the <directory> argument is not present, it reports the current directory. If the directory does no exist an appropriate error is reported.

#### clr - clear the screen
**Description**
<br />
All text on the screen is removed, resulting in an empty screen.

#### dir <directory> - list the contents of directory
**Description**
<br />
Lists the contents of directory <directory> and information about the files.
Flag options include -l (uses a long listing format).

#### echo <comment> - display <comment> on screen
**Description**
<br />
Displays <comment> on the display followed by a
new line (multiple spaces/tabs may be reduced to a single space).

#### help - display the user manual
**Description**
<br />
Displays the user manual using the more filter.

#### pause - pause shell operation
**Description**
<br />
Pauses the operation of the shell until 'Enter' key is pressed.

#### quit - quit shell
**Description**
<br />
Causes normal process termination Quits the shell

#### Other functionalities that the shell supports are indicated below:

#### stdin and stdout - I/O Redirection
**Description**
<br />
Stdin is an input stream (standard input) and it accepts text as its input. Stdout is an output stream (standard output) and is used to deliver text output text from the command to the shell. 

*Redirecting Input*: To redirect the input from a file, indicate the command, followed by the '<' redirection symbol, and then the name of the file. 

*Redirecting Output*: To redirect output to a file, indicate the command, followed by the '>' redirection symbol, and then the name of the file. The output file will be created if it does not exist and truncated if it does.
Using the '>>' redirection token will create an output file if it does not exist and append to it if it does.
stdout will be possible for the internal commands *dir*, *environ*, *echo*, and *help*.

*Redirecting Both Input and Output*: To redirect both input and output at the same time, you can use indicate the program name and its arguments that will be executed, followed by the stdin FILE stream, and then the stdout FILE stream.

#### ampersand (&) - background execution
**Description**
<br />
An ampersand (&) at the end of the command line will cause the shell to return to the command line prompt immediately after launching that program. The shell will execute the command in the background in a subshell and will not wait for the command to finish.
