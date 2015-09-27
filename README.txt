Implementation of a hash table with chaining, used to count the number of unique addresses in the trace of the memory addresses performed by a program. Linked lists are used for collision resolution. Hash table is initialized with 1000 entries. Input is a text file with 64-bit addresses. Output is the number of unique addresses in the trace.

Input format: Program takes a file name as argument from the command line. The file can have several lines to millions of lines. Each line contains an 64-bit address in hexadecimal format, e.g. 0x7f1a91026b00.

Output format: Number of unique addresses in the file, or “error” if the file does not exist.


Example program execution: 

file.txt:
0x7f1a9804ae19
0x7f1a9804ae1c
0x7f1a9804ae1c
0x7f1a9804ae1c

./count file.txt
2

./count fileEmpty.txt
0

./count fileDNE.txt
error