

# CSS parser in C++

This project was completed as part of my algorithm and data structures course, where I was tasked with implementing various data structures without the use of the STL library. These structures included a custom vector, string, and linked list.


## Operation of the application
The main goal of this project was to create a simple CSS processing engine. The engine takes in CSS sections interspersed with command sections from standard input and parses them accordingly. CSS declarations are read and placed in appropriate structures, while command sections are parsed and executed. Any resulting output (after "==") is then printed to standard output.

## Commands supported by the engine
- ???? - beginning of the command section;
- **** - resume reading CSS;
? - print the number of CSS blocks;
- i,S,? - print the number of selectors for block number i (numbering starts from 1), if there is no such block, skip;
- i,A,? - print the number of attributes for block number i, if there is no such block or attribute, skip;
- i,S,j - print the j-th selector for the i-th block (block and attribute numbers start from 1), if there is no such block or selector, skip;
- i,A,n - print the value of the attribute with name n for the i-th block, if there is no such attribute, skip;
- n,A,? - print the total (for all blocks) number of occurrences of the attribute with name n. (Duplicates should be removed at the input stage within a single block). It can be 0;
- z,S,? - print the total (for all blocks) number of occurrences of the selector z. It can be 0;
- z,E,n - print the value of the attribute with name n for block z. In case of multiple occurrences of selector z, take the last one. If there is no such attribute, skip;
- i,D,* - delete the entire block number i (i.e. separators+attributes), and after successful execution, print "deleted";
- i,D,n - delete the attribute with name n from the i-th block. If, as a result of the operation, an empty block remains, it should also be removed (along with any selectors), and after successful execution, print "deleted".


## Sample input

![Zrzut ekranu 2023-05-13 153508](https://github.com/Szymongr14/Cpp/assets/53967196/298f4748-54fd-470a-9cc8-66efc9c0cb77)

## Output

![Zrzut ekranu 2023-05-13 154221](https://github.com/Szymongr14/Cpp/assets/53967196/1fd3aa65-0823-4e97-ada2-11fa9a8e3040)