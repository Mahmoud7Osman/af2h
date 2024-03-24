## af2h - Binary to C Header Converter

The `af2h` utility is designed to convert binary files, specifically DLL files, into C header files. This enables the binary data of the DLL file to be embedded directly into a C program.

### Purpose
The purpose of this utility is to simplify the process of embedding binary data, such as DLL files, into C programs. By converting the binary data into a C header file, developers can easily include the data directly in their C code without the need for external files.

### How to Use
1. **Compilation**: Compile the `af2h.c` source code using GCC:
   ```
   gcc -o af2h af2h.c
   ```

2. **Execution**: Run the compiled executable with the following command-line arguments:
   ```
   ./af2h -f inputFile -o outputFile.h
   ```
   - `-f inputFile`: Specifies the input binary file (DLL file).
   - `-o outputFile.h`: Specifies the output C header file.

### Example
To convert a DLL file named `example.dll` into a C header file named `example.h`, execute the following command:
```
./af2h -f example.dll -o example.h
```

### Dependencies
This utility relies on standard C libraries and system calls. No external dependencies are required.

### License
This utility is provided under the [MIT License](https://opensource.org/licenses/MIT). See the `LICENSE` file for details.

### Contributions
Contributions are welcome! Feel free to submit bug reports, feature requests, or pull requests through GitHub.

### Author
This utility was developed by ([Mahmoud Osman](https://github.com/Mahmoud7Osman)).
