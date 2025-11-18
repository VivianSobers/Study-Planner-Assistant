# Study Planner Assistant

## **Team Members**

- Vivian Sobers E: PES1UG24CS901
- Dhawal Pathak: PES1UG24CS151
- Aryan Upadhyay: PES1UG25CS806

---

## Problem Statement

Students face significant challenges in organizing their academic schedules effectively. Managing multiple subjects with complex prerequisite relationships becomes overwhelming, especially when subjects build upon each other in hierarchical patterns. The key problems include:

1. **Prerequisite Management Complexity**: Students must manually track which subjects are prerequisites for others, leading to confusion and potential errors in course selection and study sequencing.

2. **Inefficient Study Sequences**: Without proper planning tools, students often study subjects in suboptimal orders that violate prerequisite requirements, resulting in gaps in foundational knowledge.

3. **Circular Dependency Risks**: Manual planning can inadvertently create impossible study plans where subjects form circular prerequisite chains (e.g., Subject A requires B, B requires C, and C requires A).

4. **Workload Imbalance**: Students struggle to distribute their study time evenly across subjects, leading to over-allocation in some areas (causing burnout) and under-preparation in others (resulting in poor performance).

5. **Time-Consuming Manual Planning**: Creating and maintaining study schedules manually is tedious, error-prone, and requires frequent revisions as course requirements change.

---

## Proposed Solution

We developed a **command-line Study Planner Assistant** that leverages graph theory and algorithmic optimization to address these challenges comprehensively. Our solution provides:

### Core Features

1. **Graph-Based Dependency Tracking**: Uses a directed graph data structure with adjacency lists to represent and manage prerequisite relationships between subjects efficiently.

2. **Automated Study Order Generation**: Implements Kahn's topological sorting algorithm to automatically generate valid study sequences that respect all prerequisite constraints.

3. **Circular Dependency Detection**: Identifies and reports impossible prerequisite chains before they cause problems, ensuring all study plans are feasible.

4. **Workload Balance Analysis**: Performs statistical analysis to identify over-allocated (>130% of average), well-balanced (70-130% of average), and under-allocated (<70% of average) subjects.

5. **Interactive Management Interface**: Provides a user-friendly command-line menu system for adding, updating, removing subjects and dependencies, and viewing analysis results.

### Technical Approach

- **Language**: C (for performance and portability)
- **Data Structures**: Directed graph with adjacency lists, array of structures
- **Algorithm**: Kahn's algorithm for topological sorting (O(V+E) time complexity)
- **Architecture**: Three-layer design (UI, Design Logic, Data Structure)

---

## Project Report

### 1. Overview

The Study Planner Assistant is a software application designed to help students organize their study schedules intelligently. By modeling subject prerequisites as a directed graph, the system can automatically determine optimal study orders and provide insights into workload distribution.

### 2. System Architecture

The application follows a modular, layered architecture:

- **User Interface Layer (main.c)**: Handles all user interactions through a menu-driven CLI
- **Design Logic Layer (planner.c/h)**: Implements core planning functionality and analysis features
- **Data Structure Layer (graph.c/h)**: Provides graph operations and topological sorting

### 3. Key Components

#### Subject Management
- Add subjects with name, study hours, and priority
- Update study hours and priorities dynamically
- Remove subjects (automatically removes associated dependencies)
- View all subjects with complete details

#### Dependency Management
- Define prerequisite relationships between subjects
- Remove dependencies when course requirements change
- Automatic validation to prevent invalid relationships

#### Intelligent Analysis
- **Study Order Generation**: Uses topological sort to create valid study sequences
- **Balance Analysis**: Identifies workload distribution issues
- **Cycle Detection**: Prevents impossible prerequisite chains

### 4. Algorithm Details

**Kahn's Algorithm for Topological Sorting**:
1. Calculate in-degree (number of prerequisites) for all subjects
2. Initialize queue with subjects having zero prerequisites
3. While queue is not empty:
   - Remove a subject and add to result
   - Decrement in-degree of dependent subjects
   - Add newly zero in-degree subjects to queue
4. If all subjects processed: valid order found
   If unprocessed subjects remain: circular dependency detected

**Time Complexity**: O(V + E) where V = vertices (subjects), E = edges (dependencies)

### 5. Implementation Highlights

- **Memory Management**: Proper allocation and deallocation with no memory leaks
- **Error Handling**: Comprehensive input validation and error reporting
- **Scalability**: Supports up to 100 subjects and dependencies
- **Cross-Platform**: Runs on Windows, macOS, and Linux

### 6. Impact and Benefits

- **Time Savings**: Automated planning reduces scheduling time from hours to minutes
- **Error Prevention**: Eliminates manual planning errors and impossible schedules
- **Optimal Learning**: Ensures prerequisites are satisfied before advanced topics
- **Balanced Workload**: Helps students distribute effort effectively across subjects
- **Academic Success**: Improved organization leads to better preparation and performance

---

## Console Commands to Run the Code

### Compilation
```bash
gcc graph.h planner.h main.c planner.c graph.c 
```

### Execution
```bash
./a.exe #Windows
./a.out #macOS and Linux
```

---

## File Descriptions

### 1. **main.c**
Entry point of the application. Implements the interactive command-line interface menu system that allows users to manage their study plan. Handles user input, validates choices, and calls appropriate functions from the planner module.

### 2. **planner.c**
Core implementation of the study planner logic. Manages subject data, dependencies, and provides analysis features like balance checking and study order generation. Acts as the business logic layer between the UI and the graph data structure.

### 3. **planner.h**
Header file defining the planner module's data structures and function prototypes. Defines the `Sub` (Subject) structure and `Plan` structure that holds all subjects and their dependency graph.

### 4. **graph.c**
Implementation of a directed graph data structure using adjacency lists. Provides graph operations and topological sorting algorithm for determining study order based on prerequisites.

### 5. **graph.h**
Header file defining the graph data structure and its operations. Includes the `Node` structure for adjacency lists and `Graph` structure.

---

## Function Descriptions

### main.c Functions

#### `int main()`
**Purpose**: Entry point that initializes the planner and runs the main menu loop.

**Parameters**: None

**Returns**: 
- `0` on successful exit
- `1` if initialization fails

**Description**: Creates a study planner, displays a menu with 10 options, processes user choices through a switch statement, and frees resources before exiting.

---

### planner.c Functions

#### `Plan *initPlan(void)`
**Purpose**: Initializes a new study plan structure.

**Parameters**: None

**Returns**: 
- Pointer to newly created `Plan` structure
- `NULL` if allocation fails

**Description**: Allocates memory for a plan, creates the dependency graph, initializes subject count to 0, and marks all subjects as inactive.

---

#### `void freePlan(Plan *p)`
**Purpose**: Frees all memory associated with a plan.

**Parameters**:
- `p`: Pointer to the plan to free

**Returns**: None

**Description**: Deallocates the graph and plan structure, preventing memory leaks.

---

#### `int findById(const Plan *p, int id)`
**Purpose**: Locates a subject by its ID.

**Parameters**:
- `p`: Pointer to the plan
- `id`: Subject ID to find

**Returns**: 
- Array index of subject if found
- `-1` if not found

**Description**: Linear search through the subjects array to find an active subject with matching ID.

---

#### `int addSub(Plan *p, const char *name, int hrs, int pri)`
**Purpose**: Adds a new subject to the study plan.

**Parameters**:
- `p`: Pointer to the plan
- `name`: Subject name (string)
- `hrs`: Study hours required
- `pri`: Priority level

**Returns**: 
- Subject ID (non-negative) on success
- `-1` on failure

**Description**: Validates inputs, checks for duplicate names, finds an empty slot, creates new subject with unique ID, and increments subject count.

---

#### `int updHrs(Plan *p, int id, int hrs)`
**Purpose**: Updates the study hours for a subject.

**Parameters**:
- `p`: Pointer to the plan
- `id`: Subject ID
- `hrs`: New hours value

**Returns**: 
- `0` on success
- `-1` on failure

**Description**: Finds subject by ID and updates its hours field.

---

#### `int updPri(Plan *p, int id, int pri)`
**Purpose**: Updates the priority level of a subject.

**Parameters**:
- `p`: Pointer to the plan
- `id`: Subject ID
- `pri`: New priority value

**Returns**: 
- `0` on success
- `-1` on failure

**Description**: Finds subject by ID and updates its priority field.

---

#### `int remSub(Plan *p, int id)`
**Purpose**: Removes a subject from the plan.

**Parameters**:
- `p`: Pointer to the plan
- `id`: Subject ID to remove

**Returns**: 
- `0` on success
- `-1` on failure

**Description**: Marks subject as inactive, decrements count, and removes all dependencies (both incoming and outgoing edges).

---

#### `int addDep(Plan *p, int from, int to)`
**Purpose**: Adds a prerequisite dependency between subjects.

**Parameters**:
- `p`: Pointer to the plan
- `from`: Prerequisite subject ID
- `to`: Dependent subject ID

**Returns**: 
- `0` on success
- `-1` on failure

**Description**: Validates both subjects exist and creates a directed edge in the graph representing the dependency.

---

#### `int remDep(Plan *p, int from, int to)`
**Purpose**: Removes a dependency between subjects.

**Parameters**:
- `p`: Pointer to the plan
- `from`: Prerequisite subject ID
- `to`: Dependent subject ID

**Returns**: 
- `0` on success
- `-1` if dependency not found

**Description**: Removes the directed edge from the graph.

---

#### `void showPlan(const Plan *p)`
**Purpose**: Displays all subjects with their details.

**Parameters**:
- `p`: Pointer to the plan

**Returns**: None

**Description**: Prints formatted list of all active subjects showing ID, name, hours, and priority.

---

#### `void showBal(const Plan *p)`
**Purpose**: Analyzes workload balance across subjects.

**Parameters**:
- `p`: Pointer to the plan

**Returns**: None

**Description**: Calculates total and average hours, then classifies each subject as over-allocated (>130% avg), under-allocated (<70% avg), or well-balanced.

---

#### `void showOrder(const Plan *p)`
**Purpose**: Generates and displays recommended study order.

**Parameters**:
- `p`: Pointer to the plan

**Returns**: None

**Description**: Uses topological sort to order subjects respecting dependencies. Detects and reports circular dependencies. Displays ordered list with subject details.

---

### graph.c Functions

#### `Graph *createGraph(void)`
**Purpose**: Creates a new empty graph.

**Parameters**: None

**Returns**: 
- Pointer to new `Graph` structure
- `NULL` if allocation fails

**Description**: Allocates graph structure and initializes all adjacency list pointers to NULL.

---

#### `void freeGraph(Graph *g)`
**Purpose**: Deallocates all graph memory.

**Parameters**:
- `g`: Pointer to the graph

**Returns**: None

**Description**: Iterates through all adjacency lists, frees each node, then frees the graph structure.

---

#### `int hasEdge(Graph *g, int from, int to)`
**Purpose**: Checks if an edge exists between two vertices.

**Parameters**:
- `g`: Pointer to the graph
- `from`: Source vertex
- `to`: Destination vertex

**Returns**: 
- `1` if edge exists
- `0` otherwise

**Description**: Traverses the adjacency list of the source vertex looking for the destination.

---

#### `int addEdge(Graph *g, int from, int to)`
**Purpose**: Adds a directed edge to the graph.

**Parameters**:
- `g`: Pointer to the graph
- `from`: Source vertex
- `to`: Destination vertex

**Returns**: 
- `0` on success
- `-1` on failure

**Description**: Validates inputs, prevents self-loops, checks for duplicate edges, creates new node, and inserts at head of adjacency list.

---

#### `int remEdge(Graph *g, int from, int to)`
**Purpose**: Removes a directed edge from the graph.

**Parameters**:
- `g`: Pointer to the graph
- `from`: Source vertex
- `to`: Destination vertex

**Returns**: 
- `0` on success
- `-1` if edge not found

**Description**: Searches adjacency list, unlinks node, and frees memory.

---

#### `void topoSort(Graph *g, int ids[], int n, int res[], int *sz)`
**Purpose**: Performs topological sort on specified vertices.

**Parameters**:
- `g`: Pointer to the graph
- `ids`: Array of vertex IDs to sort
- `n`: Number of vertices
- `res`: Output array for sorted order
- `sz`: Output parameter for result size (or `-1` if cycle detected)

**Returns**: None (uses output parameters)

**Description**: Implements Kahn's algorithm using in-degree tracking. Repeatedly selects vertices with in-degree 0, adds to result, and decrements in-degree of neighbors. Sets `*sz = -1` if circular dependency detected.

---

## Variable Description Tables

### Main Variables (main.c)

| Variable | Type | Scope | Description |
|----------|------|-------|-------------|
| `p` | `Plan*` | Local | Pointer to the main plan structure |
| `run` | `int` | Local | Loop control flag (1=continue, 0=exit) |
| `in` | `char[100]` | Local | Buffer for string input |
| `nm` | `char[NAME_MAX]` | Local | Buffer for subject name |
| `id` | `int` | Local | Subject ID for operations |
| `hrs` | `int` | Local | Study hours input |
| `pri` | `int` | Local | Priority level input |
| `f` | `int` | Local | "From" vertex for dependencies |
| `t` | `int` | Local | "To" vertex for dependencies |
| `ch` | `int` | Local | Menu choice selected by user |

---

### Plan Structure Variables (planner.h)

| Variable | Type | Description |
|----------|------|-------------|
| `subs` | `Sub[MAX_SUB]` | Array of subject structures |
| `cnt` | `int` | Count of active subjects |
| `g` | `Graph*` | Pointer to dependency graph |

---

### Subject Structure Variables (planner.h)

| Variable | Type | Description |
|----------|------|-------------|
| `id` | `int` | Unique subject identifier |
| `name` | `char[NAME_MAX]` | Subject name (max 64 chars) |
| `hrs` | `int` | Required study hours |
| `pri` | `int` | Priority level |
| `act` | `int` | Active flag (1=active, 0=inactive) |

---

### Graph Structure Variables (graph.h)

| Variable | Type | Description |
|----------|------|-------------|
| `adj` | `Node*[MAX_V]` | Adjacency list array (max 100 vertices) |

---

### Node Structure Variables (graph.h)

| Variable | Type | Description |
|----------|------|-------------|
| `v` | `int` | Vertex ID (destination) |
| `next` | `Node*` | Pointer to next node in list |

---

### Local Variables in Functions

#### showBal() Function
| Variable | Type | Description |
|----------|------|-------------|
| `tot` | `int` | Total hours across all subjects |
| `avg` | `double` | Average hours per subject |

#### showOrder() Function
| Variable | Type | Description |
|----------|------|-------------|
| `ids` | `int[MAX_SUB]` | Array of active subject IDs |
| `n` | `int` | Number of active subjects |
| `res` | `int[MAX_SUB]` | Result array for sorted order |
| `sz` | `int` | Size of result array |

#### topoSort() Function
| Variable | Type | Description |
|----------|------|-------------|
| `ind` | `int[MAX_V]` | In-degree array for each vertex |
| `vis` | `int[MAX_V]` | Visited flag array |
| `idx` | `int` | Current index in result array |
| `proc` | `int` | Count of processed vertices |
| `found` | `int` | Flag indicating if vertex with in-degree 0 found |

---

## Constants (PPDs)

| Constant | Value | Description |
|----------|-------|-------------|
| `NAME_MAX` | 64 | Maximum length for subject name |
| `MAX_SUB` | 100 | Maximum number of subjects |
| `MAX_V` | 100 | Maximum number of graph vertices |

---

## Usage Example

### Sample Workflow

1. **Add Subjects**:
   - DSA (40 hours, Priority 1)
   - DDCO (50 hours, Priority 2)
   - AFLL (35 hours, Priority 1)

2. **Define Dependencies**:
   - DSA → DDCO
   - DDCO → AFLL

3. **Generate Study Order**:
   - System outputs: DSA → DDCO → AFLL

4. **Check Balance**:
   - DSA: Well-balanced
   - DDCO: Over-allocated (20% above average)
   - AFLL: Under-allocated (16% below average)

---

## Future Enhancements

1. **Data Persistence**: Save and load study plans from files
2. **GUI Interface**: Web or desktop application
3. **Calendar Integration**: Link subjects to specific dates and deadlines
4. **Progress Tracking**: Mark subjects as completed and track study time
5. **Priority-Based Sorting**: Factor priority levels into study order generation
6. **Multi-User Support**: Individual user accounts and plans
7. **Statistics Dashboard**: Visual analytics of study patterns
8. **Mobile Application**: iOS and Android versions

---

## Conclusion

The Study Planner Assistant successfully addresses the challenges of academic schedule management through intelligent algorithmic approaches. By leveraging graph theory and topological sorting, the system provides students with automated, error-free study planning that respects prerequisite constraints and promotes balanced workload distribution. The modular architecture ensures maintainability and provides a foundation for future enhancements.
