# Touring machine

## Usage

### Compilation

Clone the repository and compile the `touring.c` file.

For example, using `gcc`:

```zsh
gcc touring.c -o touring
```

### Execute an example file

After compiling, execute the following command:

```zsh
./touring examples/palindrome.txt 1011010
```

Here, `1011010` represents the initial state of the tape. If everything is functioning correctly, you should observe the following output:

```
Loading provided tape...
0100101
```

## Advanced usage

When launching the program, provide the following parameters:

- **state file** (mandatory)
- **initial state** of the **tape** (optional)

```zsh
./touring stateFile Tape
```

## Creating Your State File

A state file is a text file that defines the states of the touring machine.

The machine can execute four instructions:

- `N` next, advance the tape by 1
- `B` back, retreat the tape by 1
- `W` writes on the tape
  > Example: `W1` writes 1
- `R` reads from the tape and sets the state of the machine to whatever is written on the tape

Each state is defined by one char in the following way:

```
:N
```

where `N` can be any char.

- Every file must contain at least one state, and the name of the state is not important.
- You can use tabs, spaces, and newlines as you wish.
- When the machine reads a state that is not defined, the program comes to an end.

### Example:

```
:S //declare the S state
R  //read from the tape
:1 //declare the 1 state
W0 //write 0 on the tape
N //advance the tape
R //read from the tape
:0 //declare the 0 state
W1 //write 1 on the tape
N //advance the tape
R //read from the tape
```

> WARNING
>
> Avoid using comments in your state files as they won't work.
