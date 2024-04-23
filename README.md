# Linking Wikipedia Pages

Program that analyzes the connectivity of Wikipedia pages from [SNAP Dataset](https://snap.stanford.edu/data/enwiki-2013.html) using three graph algorithms: Breadth-First Search (BFS), Iterative Deepening Depth-First Search (IDDFS), and simplified PageRank.



## Directory

- **entry:** Contains the `main.cpp` file, which serves as the entry point for running our algorithms on a graph. Users can choose to create a graph from the full dataset.

- **src:** Contains the source code for the project. It includes two classes: `DataParser` and `Graph`. The `Graph` class represents the graph data structure and provides functions for running various algorithms. The `DataParser` class is responsible for parsing the data files and populating the graph accordingly.

- **tests:** Contains test cases for all the functions implemented in the project.

- **bin:** Contains the executables `exec` and `tests`, which will be generated when the user runs the program.

## Functionality

The project offers the following functionality:

1. **Graph Creation and Algorithms:** The `main.cpp` file allows users to interactively create a graph and run algorithms on it. Users can run the algorithms on the full dataset. They can select one of the available algorithms and specify parameter values. The program then executes the chosen algorithm and displays the results in the terminal. Users can either terminate the program or choose to run another algorithm.

2. **Graph Class:** The `Graph` class provides a data structure for representing graphs and includes functions for running algorithms on the graph structure.

3. **DataParser Class:** The `DataParser` class is responsible for parsing the data files and populating the graph with the provided data.

## Running the Project

Clone the repo in your desired repository by running:

`git clone https://github.com/kpulgari/Linking-Wikipedia-Pages.git`

**IMPORTANT:** To run analysis on full dataset download both files from [snap.stanford.edu](https://snap.stanford.edu/data/enwiki-2013.html) and put them in a folder titled `\lib` in the root of repository.

To run the **main** function:

1. Run `make` to build the project.
2. Execute `./bin/exec` in the terminal.
3. Follow the prompts in the terminal to create a graph and run the desired algorithms.

To run the **tests**:

1. Run `make tests` to build the project's test cases.
2. Execute `./bin/tests` in the terminal to run all the test cases.
3. Optionally, run `./bin/tests xxx` to run a specific test case, replacing `xxx` with the tag of the desired test case.

Feel free to explore the project and experiment with different inputs and algorithms!
