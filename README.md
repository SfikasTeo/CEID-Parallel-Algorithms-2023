## Introduction: 
As a part of the course: "**Parallel Algorithms**" from the *[University of Patras](https://www.upatras.gr/en/)* and the Department of *[Computer Engineering and Informatics](https://www.ceid.upatras.gr/en/)*    
We will showcase a parallel algorithm described in the book "**[Introduction to Parallel Algorithms and Architectures](https://www.elsevier.com/books/introduction-to-parallel-algorithms-and-architectures/leighton/978-1-4832-0772-8)**" written by [F. Thomson Leighton](https://en.wikipedia.org/wiki/F._Thomson_Leighton).   
We will focus on a simple implementation of a **greedy parallel package routing problem on a linear topology** under the chapter *1.7.1*.       
For the simulation of the problem we will mainly be using **[c++](https://en.wikipedia.org/wiki/C++)**, while the parallel enviroment will be simulated with the help of threads *(nodes)* and the **[openmp](https://www.openmp.org/) API**.   
  
## About the Algorithm:
The algorithms is described in chapter: *1.7.1 Greedy Algorithms* in leighton's book.  
In summary we will focus on ways of routing the correct information and pacakges between the nodes of specific topologies and architectures.
We will consider a **linear topology** of **N** nodes, in which exists an arbitrary amount of packages in each node, each destined for different nodes in the architecture.
In each step of the algorithm, from each node one package can be transmitted in each direction. In case of **more than one** packages contesting for the **same** edge and direction of the network, the rule of "*Furthest first contetion resolution*" will be followed. Meaning that the package with the furthest nodes left to travesrse will be deemed as the **priority package**.  
According to the **lemma 1.5** that is detailedy proven the algorithm must stop in **O(N-1) steps**.
![image](https://user-images.githubusercontent.com/65178946/230637725-4fa2a6e7-53f4-4b11-a64e-38b2ab376368.png)

## About the Implementation:
Apart from the code beeing available inside of the repository it is also **available** as a collaboration session in the following link: **[replit-sfikasteo](https://replit.com/join/crhukhrgol-sfikasteo)**. Inside the repository there is also a **video file** with am example step by step execution.  
Some quick guidelines for the execution:
* Compilation can be done using the configured makefile from the shell: `make`. Executing the code is as simple as `./packageRouting`
* In the begging the number of nodes will be asked, An **integer** value should be given through *stdin*.
* The nodes will be executing in parallel, in the first step of the algorithm each node will ask for its initial packages.
  * **Interger** values should be given: *0 < value < N*, signifying the **destination** node. **Any** value outside these boundaries will signify that we wish to stop inserting packages in the node.
  * Leaving a node **initially** empty of packages is possible by inserting any *destination* value outside of the boundaries *( -1 for example )*.
  * Inserting a package in any node *j*, that is destined for node *j* will automatically be resolved.
* Due to the random scheduling of threads, **no** two executions will provide the output messages in the **same order**, but all will provide the **same result**.   

https://user-images.githubusercontent.com/65178946/230641534-7a2f7ae6-cd6e-4d40-ae28-c9b564c0364a.mp4


