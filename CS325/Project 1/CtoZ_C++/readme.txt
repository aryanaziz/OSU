Written in C++ and tested on flip, compile it on the command line via: "g++ CtoZ.cpp"

The program, by default, is set to pull the data from a separate text file. The program will NOT run without specifying the input file via the command line. 
Run the program via: "./outputFile filename.txt" 
Where outputFile is the name of the compiled c++ file, and filename.txt is the name of your input text. 

The program is modular and can be changed to accept arrays of any size. On line 18, you will see a constant: const int arraySize = 100;
Changing that integer value will change the size of the array. Recompile and run again with a different input text document. 