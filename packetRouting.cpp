#include <iostream>
#include <bits/stdc++.h>
#include <omp.h>


// ----------------- Generic Guide lines -----------------

// - Compile with: g++ -O3 -Wall -std=c++11 -lstdc++ -fopenmp packetRouting.cpp 
// - Or use the makefile: make.
// - OPENMP: Run with: ./executable_name

// ----------------- Introdution -----------------

// N = number of nodes
// M = number of packets

// Openmp will be used to simulate the network of N nodes
// Each node will have a double ended priority queue of packets
// to be sent to the neighboring nodes.

// Each step will be simulated according to the instructions of 
// Leighton. The nodes will be numbered from 0 to N-1 and will be
// "arranged" linearly.
// In each step One packet may be sent from each node in each direction.
// The edge contention is resolved by the nodes with the furthest distance.
// Scheduling will follow the "furthest first contention resolution" protocol.
// We are following a greedy approach to the routing of the packets.

// packets will be simulated as a single integer denoting the packet number.
// A more proper simulation could involve a custom structured datatype
// packets for each node will be given by the user.

// We will implement a generalized form of the algorithm without the restrictions
// of the starting number of packets per node = 1 ( Of course 1 packet per node
// is possible). More than two packets also can 
// contend for the same network edge. As illustrated in the example figure 1.9 and 
// pages 157-159 of Leighton's book. 

// ----------------- Auxilliary Definitions -----------------

int num_active_packets = 0; // Variable for counting packets
int num_threads; // Total number of nodes

// Structure of double-ended priority queue
struct DoubleEndedPriorityQueue {
    std::multiset<int> st;
    // Returns size of the queue. Works in
    // O(1) time
    int size() { return st.size(); }
    // Returns true if queue is empty.
    // Works in O(1) time
    bool isEmpty() { return (st.size() == 0); }
    // Inserts an element.
    // Works in O(log n) time
    void insert(int x) { st.insert(x); }
    // Returns minimum element.
    // Works in O(1) time
    int getMin() { return *(st.begin()); }
    // Returns maximum element.
    // Works in O(1) time
    int getMax() { return *(st.rbegin()); }
    // Deletes the minimum element.
    // Works in O(log n) time
    void deleteMin() {
        if (st.size() == 0)
            return;
         auto it = st.begin();
        st.erase(it);
    }
     // Deletes the maximum element.
    // Works in O(log n) time
    void deleteMax() {
        if (st.size() == 0)
            return;
         auto it = st.end();
        it--;
        st.erase(it);
    }
	// pops the minimum element.
    // Works in O(log n) time
	int popMin() {
		int min = getMin();
		deleteMin();
		return min;
	}
	// pops the maximum element.
	// Works in O(log n) time
	int popMax() {
		int max = getMax();
		deleteMax();
		return max;
	}
};

void printQueue(struct DoubleEndedPriorityQueue Queue) {
	std::cout << "Queue: ";
	for (auto it = Queue.st.begin(); it != Queue.st.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void addpackets(struct DoubleEndedPriorityQueue &Queue, int node_id) {
	std::cout << "Node: ["<< node_id <<"] "<< " Insert new packets, by their destination nodes ( 0..N-1 ). Add -1 to exit"  << std::endl;
	int packet = node_id;
	while (1) {
		std::cout << "New packet destined for node: ";
		std::cin >> packet;
		if (packet == node_id  || packet < 0 || packet >= num_threads)
			break;

		Queue.insert(packet);
		#pragma omp atomic
		num_active_packets++;
	}
}

int main(int argc, char **argv) {
	// Ask user for the number of nodes
	std::cout << "Insert the number of nodes of the topology: ";
	// initialize variables:
	std::cin >> num_threads; // Total number of nodes

	omp_set_num_threads(num_threads); // Set number of threads
	omp_set_dynamic(0); // Disable dynamic adjustment of threads

	int step; // Variable for counting steps
	
	// Allocate memory for the transferrence of packets
	int *left_transmitted_packets = (int *)malloc((num_threads) * sizeof(int));
	int *right_transmitted_packets = (int *)malloc((num_threads) * sizeof(int));

	// Initialize the network of nodes
	#pragma omp parallel
	{
		// Declare the place in the topology of the node
		int node_id = omp_get_thread_num();
		
		// Initialize a priority queue for each node
		struct DoubleEndedPriorityQueue nodeQueue;
		
		// Add packets to the queue
		#pragma omp critical
		{
			addpackets(nodeQueue, node_id);
		}
		// Syncronize the nodes
		#pragma omp barrier

		// Initialize the variables for the transferrence of packets
		int left_received_packet = -1;
		int right_received_packet = -1;

		// Initialize the algorithm of Greedy routing in a linear topology
		// In each step each node will send a packet to the left and to the right
		// The edge contention is resolved by the nodes with the furthest distance

		while(num_active_packets){
			#pragma omp single
			{
				std::cout << "-------------- Step: " << ++step << " --------------" << std::endl;
			}
			
			// Exmplaining the logic of the following code: 
			// Send the packet with the smallest value to the left node if value is smaller than rank
			// Send the packet with the largest value to the right node if value is larger than rank
			
			// Send packet with smallest value to the left node
			left_transmitted_packets[node_id] = (!nodeQueue.isEmpty() && (nodeQueue.getMin() < node_id))?nodeQueue.popMin():-1;
			// Send packet with largest value to the right node
			right_transmitted_packets[node_id] = (!nodeQueue.isEmpty() && (nodeQueue.getMax() > node_id))?nodeQueue.popMax():-1;

			// Syncronize the nodes
			#pragma omp barrier
			
			// Receive packets from the left nodes	
			if ( (node_id != 0) && right_transmitted_packets[node_id-1] != -1 ) {
				left_received_packet = right_transmitted_packets[node_id-1];
				if ( left_received_packet != node_id ) {
					nodeQueue.insert(left_received_packet);
					#pragma omp critical
					{
						std::cout << "Node: ["<< node_id <<"] "<< " Received packet from node: [" << node_id-1 << "] destined for node: [" << left_received_packet << "]" << std::endl;
					}
				}
				else {
					#pragma omp critical
					{
						std::cout << "Node: ["<< node_id <<"] "<< " packet was delivered from node: [" << node_id-1 << "]" << std::endl;
					}
					#pragma omp atomic
					num_active_packets--;
				}
			}

			// Receive packets from the right nodes
			if ( (node_id != num_threads-1) && left_transmitted_packets[node_id+1] != -1 ) {
				right_received_packet = left_transmitted_packets[node_id+1];
				if ( right_received_packet != node_id ) {
					nodeQueue.insert(right_received_packet);
					#pragma omp critical
					{
						std::cout << "Node: ["<< node_id <<"] "<< " Received packet from node: [" << node_id+1 << "] destined for node: [" << right_received_packet << "]" << std::endl;
					}
				}
				else {
					#pragma omp critical
					{
						std::cout << "Node: ["<< node_id <<"] "<< " packet was delivered from node: [" << node_id+1 << "]" << std::endl;
					}
					#pragma omp atomic
					num_active_packets--;
				}
			}

			// Synchronize and move to the next step: 
			#pragma omp barrier
		}
	}
	std::cout << "--------- Finished in step: ["<< step <<"] ---------" << std::endl;
	return 0;
}
