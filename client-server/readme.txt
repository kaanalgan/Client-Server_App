##### CENG421 ASSIGNMENT#2 CLIENT-SERVER #####

Student ID: 250201036
Student Name: Kaan ALGAN

Implementation Details: 
-----------------------

    • client.c → takes two integer inputs from the user, formats them with htons then send them to the localhost with port 8080 then waits for server.c to perform summation and return the result to be able to display it.
      
    • server.c → takes two integer inputs from the client.c via port 8080, sums them up, returns the result back to the client.c after formatting them with htons.



Execution:
----------
	gcc server.c -o server-out
	./server-out 8080

	gcc client.c -o client-out
	./client-out localhost 8080

