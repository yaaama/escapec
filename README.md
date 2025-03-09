# `escapec`

## About

When we want to define a string literal in C/C++, we need to ensure that the
text is properly escaped.

**This tool is made for that purpose.**

## Usage

### Piping input

You can pipe input like so:

```shell
$ echo -n 'some%random"badtext' | escapec
```

Which produces:

> "some%%random\"badtext"

Which you can use in C code, like so:

```c
char *good_text = "some%%random\"badtext";
```

Note that there are now _2_ `%` characters. To print `%`, you must escape it with with another.

By default it is escaped, however you may turn it off using the `-p` flag.

### Specifying a file to read from

You can also specify a file like so:

```shell
$ escapec json.txt
```

Which will print the result to standard output.

If you want to capture the output and store it in another file, it is a trivial task:

```shell
$ escapec json.txt > escaped_json.txt
```

### Flags and Options

- **-p** `escapec` will not escape away `%` characters.
- **-n** Terminate `escapec` output using a null terminator rather than with a new line.
- **-s** Break output on new-line(s). This is useful if you want to retain the
  line-breaks present in the original text.
- **-h** Prints an explanation of the options above.

## Building

1. Clone the repository.

```shell
git clone https://github.com/yaaama/escapec.git
```

2. Enter the cloned repository.

```shell
cd escapec
```

3. Make it.

```shell
make
```

4. You can then copy the script to your local scripts folder (typically
   `$HOME/.local/bin/`):

```shell
cp ./escapec $HOME/.local/bin/
```

---

## Note

If there are any issues with the code or you find any bugs, I encourage you to
create an issue and I will do my best to look into it.
