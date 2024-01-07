# USF COP 4600 Operating Systems: Project 3 Description

This proejct designs and implements a readers/writers lock using semaphores that do not starve the readers and do not starve the writers.

### To compile the program:

- Run make, to compile all the files.
- Make sure to include main.c in the same directory.
- Alternatively, could also run gcc -o rwmain main.c readerwriter.c -l pthread.

### To run the program:

- Include scenarios.txt to run an scenario for the program.
- In addition, you could modify that scenario to test other scenarios (1 scenario per run). 
- run ./rwmain to see the result.
- The example used in scenarios.txt is "rrrrwrrr". The result below should be something similar to that.

### Example

$ make
gcc	-o	rwmain	main.c	readerwriter.c	-l	pthread
 ./rwmain

Scenario Starts:

<sup>
Create reader<br>
Create reader<br>
Reader's is in... reading<br>
Create reader<br>
Reader's is in... reading<br>
Finished reading<br>
Finished reading<br>
Create reader<br>
Reader's is in... reading<br>
Finished reading<br>
Create writer<br>
Reader's is in... reading<br>
Finished reading<br>
Create reader<br>
Writer's is in... writing<br>
Finished writing<br>
Create reader<br>
Reader's is in... reading<br>
Create reader<br>
Finished reading<br>
Reader's is in... reading<br>
Finished reading<br>
Reader's is in... reading<br>
Finished reading
</sup>
