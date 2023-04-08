## Introduction: 
As a part of the course: "**Parallel Algorithms**" from the *[University of Patras](https://www.upatras.gr/en/)* and the Department of *[Computer Engineering and Informatics](https://www.ceid.upatras.gr/en/)*    
We will showcase a parallel algorithm described in the book "**[Introduction to Parallel Algorithms and Architectures](https://www.elsevier.com/books/introduction-to-parallel-algorithms-and-architectures/leighton/978-1-4832-0772-8)**" authored by [F. Thomson Leighton](https://en.wikipedia.org/wiki/F._Thomson_Leighton).   
We will focus on a simple implementation of a **greedy parallel packet routing problem on a linear topology** as described in chapter *1.7.1*.       
For the implementation of the algorithm we will mainly be using **[c++](https://en.wikipedia.org/wiki/C++)**, while the parallel enviroment will be created with the help of threads *(nodes)* and the **[openmp](https://www.openmp.org/) API**.   
  
## About the Algorithm:
The algorithms is described in chapter: *1.7.1 Greedy Algorithms* in leighton's book.  
In summary we will focus on a way of routing the correct information and packets between the nodes of a linear topology.
We will consider a **linear topology** of **N** nodes, in which exists just one packet in each node, each destined for different nodes in the architecture.
In each step of the algorithm, from each node one packet can be transmitted in each direction. 
![image](https://user-images.githubusercontent.com/65178946/230637725-4fa2a6e7-53f4-4b11-a64e-38b2ab376368.png)

## About the Implementation:
 The code in addition to being available inside the repository, is also **available** as a collaboration session at the following online collaborative programming platform: **[replit-sfikasteo](https://replit.com/join/crhukhrgol-sfikasteo)**. Inside the repository there is also a **video file** with with an indicative step-by-step execution.  
### Some quick guidelines for the execution:
* **Compilation** can be done using the configured makefile from the shell: `make` or by `g++ -O3 -std=c++11 -lstdc++ -fopenmp packetRouting.cpp`.   **Executing** the code is as simple as `./packetRouting`.
* At the begging the number of nodes *(N)* will be asked. An **integer** value should be given via *stdin*.
* In the next step, nodes will **not** be always be shown in the **same order**, due to the random thread scheduling.
* The nodes will be executing in parallel, in the first step of the algorithm each node will ask for its initial packets.
  * **Interger** values should be given: *0 < value < N*, showing the **destination** node. Any value out of this range implies that we wish to stop adding packets to the node. Where *N* is the number of nodes.
  * Leaving a node with no packets is possible by setting the input value to any destination value out of the range: *value<N or value<1 (e.g., -1)*.       Where *N* is the number of nodes.
  * Inserting a packet in any node *j*, that is destined for node *j* will automatically be resolved.
* Due to the random scheduling of threads *(the different nodes)*, **no** two executions will provide the output messages in the **same order**, but all will provide the **same result**.   

https://user-images.githubusercontent.com/65178946/230641534-7a2f7ae6-cd6e-4d40-ae28-c9b564c0364a.mp4


