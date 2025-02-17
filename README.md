# Oblivious Data Structures Project

This project implements several oblivious data structures in C++ based on the research paper:

> Xiao Shaun Wang, Kartik Nayak, Chang Liu, T-H. Hubert Chan, Elaine Shi, Emil Stefanov, Yan Huang.  
> **Oblivious Data Structures**. Cryptology ePrint Archive, Paper 2014/185, 2014.  
> DOI: [10.1145/2660267.2660314](https://eprint.iacr.org/2014/185)

The implementation includes:
- **Oblivious Stack** – A linked-list based stack with `Push` and `Pop` operations.
- **Oblivious Queue** – A linked-list based queue with `Enqueue` and `Dequeue` operations.
- **Oblivious Priority Queue** – An array-based heap (using a `readPath` function to avoid revealing random access patterns) with `Insert` and `ExtractMin` operations.
- **Oblivious Map** – An AVL tree-based map supporting `Insert` and `Find` operations (including rotations for balancing).

## Project Structure

```
ObliviousDS_Project/ ├── main.cpp ├── Utilities.h ├── ODSClient.h ├── ObliviousStack.h ├── ObliviousStack.cpp ├── ObliviousQueue.h ├── ObliviousQueue.cpp ├── ObliviousPriorityQueue.h ├── ObliviousPriorityQueue.cpp ├── ObliviousMap.h ├── ObliviousMap.cpp ├── .gitignore └── README.md
```

## Requirements

- A C++14 or C++17 compliant compiler (e.g., g++ or clang++).
- (Optional) CMake if you prefer a CMake-based build system.

## Building the Project

### Using g++ (Command Line)

From the project root, run:

```bash
g++ -std=c++17 -o ObliviousDS_Project main.cpp ObliviousStack.cpp ObliviousQueue.cpp ObliviousPriorityQueue.cpp ObliviousMap.cpp
```

Then execute the binary:
```bash
./ObliviousDS_Project
```

## License

This project is licensed under the MIT License.

## Acknowledgments

This implementation is based on the research paper:

> Xiao Shaun Wang, Kartik Nayak, Chang Liu, T-H. Hubert Chan, Elaine Shi, Emil Stefanov, Yan Huang.  
> **Oblivious Data Structures**. Cryptology ePrint Archive, Paper 2014/185, 2014.  
> DOI: [10.1145/2660267.2660314](https://eprint.iacr.org/2014/185)

