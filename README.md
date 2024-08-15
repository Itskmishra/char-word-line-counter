# CWC (Character, Word, and Line Counter)

CWC is a simple utility to count characters, words, and lines in a file or given text.

## Features

- Count characters in a file
- Count words in a file
- Count lines in a file
- Flexible command-line interface using a custom argument parser

## Usage
```
cwc [OPTIONS] -f <filename>
```


### Options

- `-v, --version`: Print the version of the program
- `-h, --help`: Print the help message
- `-c, --charc`: Count the number of characters
- `-w, --word`: Count the number of words
- `-l, --line`: Count the number of lines
- `-f, --file <filename>`: Specify the path of the file to read from

## Examples

Count all (lines, words, and characters):
```
cwc -f example.txt
```

Count only characters:
```
cwc -c -f example.txt
```
Count only words:
```
cwc -w -f example.txt
```
Count only lines:
```
cwc -l -f example.txt
```

## Building
To build the project, make sure you have a C compiler installed. Then run:

gcc -o cwc main.c -I.
Copy
Note: The custom `argparse.h` header file should be in the same directory as `main.c`.

## Dependencies

This project uses a custom [`argparse.h`](https://github.com/Itskmishra/c-argument-parser) header file for command-line argument parsing. This header file includes the implementation of the argument parser, so no separate `.c` file is required.

### Custom Argument Parser Features
- Support for short and long option names
- Handling of flag and value type arguments
- Automatic help and version printing
- Error and warning messages with color coding
 
## Version
1.0.0
