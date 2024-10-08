# This project is about creating a simple shell.

## TO DO
Mandatory:
- [X] Display a prompt when waiting for a new command.
- [X] history
- [X] Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- [X] Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- [X] Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).
- [ ] Implement redirections:
	- [ ] < should redirect input.
	- [ ] > should redirect output.
	- [ ] << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
	- [ ] >> should redirect output in append mode.
- [X] Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- [X] Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- [X] Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- [X] Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
	- [X] ctrl-C displays a new prompt on a new line.
	- [X] ctrl-D exits the shell.
	- [X] ctrl-\ does nothing.
- [X] echo with option -n
- [X] cd with only a relative or absolute path
- [X] pwd with no options
- [X] export with no options
- [X] unset with no options
- [X] env with no options or arguments
- [X] exit with no options

Optional:
- [ ] && and || with parenthesis for priorities.
- [ ] Wildcards * should work for the current working directory
