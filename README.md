# AUTOSAR Lab - Kata Training System

A complete AUTOSAR (Automotive Open System Architecture) learning environment integrated into your katas-training repository. Practice daily coding katas while learning professional automotive software architecture.

## 🎯 What You Get

- **Complete AUTOSAR Stack**: BSW (Basic Software), RTE (Runtime Environment), and Application SWCs
- **Real-World Structure**: Industry-standard layered architecture
- **Kata Integration**: Each kata becomes a Software Component
- **Build System**: Integrated with your existing Makefile
- **Testing Ready**: Unit test structure included
- **Coverage Reports**: Track your code coverage

## 📁 Directory Structure

```
katas-training/
├── src/
│   └── autosar/
│       ├── bsw/                    # Basic Software Layer
│       │   ├── os/                 # Operating System Abstraction
│       │   │   ├── Std_Types.h    # AUTOSAR standard types
│       │   │   ├── Os.h           # OS API header
│       │   │   └── Os.c           # Simple cooperative scheduler
│       │   └── com/                # Communication Module
│       │       ├── Com.h          # COM API header
│       │       └── Com.c          # Signal routing
│       ├── rte/                    # Runtime Environment
│       │   ├── Rte_Type.h         # Common data types
│       │   ├── Rte.h              # RTE API
│       │   └── Rte.c              # RTE implementation
│       ├── swc/                    # Application Software Components
│       │   ├── template/          # Template for new katas
│       │   │   ├── Swc_Template.h
│       │   │   └── Swc_Template.c
│       │   └── kata_001/          # Example kata
│       │       ├── Swc_Kata001.h
│       │       └── Swc_Kata001.c
│       └── main.c                  # System initialization
├── test/
│   └── autosar/                    # AUTOSAR unit tests (TODO)
└── build/
    └── autosar/                    # Build artifacts
```

## 🚀 Quick Start

### 1. Setup

The files are already organized to integrate with your existing repository structure. No special installation needed beyond your current toolchain (GCC, Make).

### 2. Build and Run

```bash
# Build the AUTOSAR lab
make autosar

# Build and run
make autosar-run

# Clean build
make autosar-clean
```

### 3. Your First Run

When you run the lab, you'll see:

```
╔════════════════════════════════════════╗
║   AUTOSAR LAB - Kata Training System  ║
║         Embedded Software Practice     ║
╚════════════════════════════════════════╝

[OS] Initialized at tick 1234567
[COM] Initialized - 4 signals
[RTE] Initializing Runtime Environment...
[RTE] Port mappings configured: 6
[SWC_Template] Initialized
[OS] Starting scheduler...
```

## 📚 AUTOSAR Layers Explained

### Basic Software (BSW)

The foundation that abstracts hardware and provides services.

**OS Module** (`src/autosar/bsw/os/`)
- Simple cooperative scheduler
- Task management (1ms, 10ms, 100ms tasks)
- Timing services
- Mimics real RTOS behavior

**COM Module** (`src/autosar/bsw/com/`)
- Signal-based communication
- Data routing between components
- Update flags for change detection

### Runtime Environment (RTE)

The glue between BSW and application components.

**What it does:**
- Provides standardized APIs to application SWCs
- Routes data between components
- Abstracts communication details
- Type-safe interfaces

**Key files:**
- `Rte_Type.h` - Common data types
- `Rte.h` - API definitions
- `Rte.c` - Implementation

### Application Software Components (SWC)

Your kata implementations live here!

**Structure of a SWC:**
```c
// Initialization (called once)
void Swc_KataXXX_Init(void);

// Periodic runnable (called by OS)
void Swc_KataXXX_Runnable_10ms(void) {
    uint32 input1, input2, result;
    
    // Read from RTE
    Rte_Read_SwcKataXXX_Input1(&input1);
    Rte_Read_SwcKataXXX_Input2(&input2);
    
    // YOUR KATA LOGIC HERE
    result = solve_kata(input1, input2);
    
    // Write to RTE
    Rte_Write_SwcKataXXX_Output(result);
}
```

## 💡 Creating Your Daily Kata

### Method 1: Using the Helper Command

```bash
make new-kata
# Enter: 002
# Creates: src/autosar/swc/kata_002/
```

### Method 2: Manual Creation

```bash
# Copy template
cp -r src/autosar/swc/template src/autosar/swc/kata_002

# Navigate and rename
cd src/autosar/swc/kata_002
mv Swc_Template.h Swc_Kata002.h
mv Swc_Template.c Swc_Kata002.c

# Update content (replace Template with Kata002)
sed -i 's/Template/Kata002/g' *.h *.c
sed -i 's/TEMPLATE/KATA002/g' *.h *.c
```

### Method 3: Step-by-Step

1. **Copy the template**
   ```bash
   cp -r src/autosar/swc/template src/autosar/swc/kata_002
   ```

2. **Rename files**
   ```
   Swc_Template.h → Swc_Kata002.h
   Swc_Template.c → Swc_Kata002.c
   ```

3. **Update the header** (`Swc_Kata002.h`)
   ```c
   #ifndef SWC_KATA002_H
   #define SWC_KATA002_H
   
   void Swc_Kata002_Init(void);
   void Swc_Kata002_Runnable_10ms(void);
   void Swc_Kata002_Runnable_100ms(void);
   
   #endif
   ```

4. **Implement your kata** (`Swc_Kata002.c`)
   ```c
   #include "Swc_Kata002.h"
   #include "Rte.h"
   
   void Swc_Kata002_Init(void) {
       // Initialize your kata
   }
   
   void Swc_Kata002_Runnable_10ms(void) {
       // YOUR CODEWARS SOLUTION HERE
   }
   ```

5. **Update Makefile**
   
   Add to `AUTOSAR_SWC_SRCS`:
   ```makefile
   AUTOSAR_SWC_SRCS := $(wildcard $(AUTOSAR_SWC_DIR)/template/*.c) \
                       $(wildcard $(AUTOSAR_SWC_DIR)/kata_001/*.c) \
                       $(wildcard $(AUTOSAR_SWC_DIR)/kata_002/*.c)
   ```
   
   Add to `AUTOSAR_INCLUDES`:
   ```makefile
   AUTOSAR_INCLUDES := ... \
                       -Isrc/autosar/swc/kata_002
   ```

6. **Register in main.c**
   
   Add to `SWC_Init()`:
   ```c
   Swc_Kata002_Init();
   ```
   
   Add to `Register_SWC_Runnables()`:
   ```c
   Os_RegisterTask(TASK_10MS, Swc_Kata002_Runnable_10ms, 10, "SWC_Kata002_10ms");
   Os_RegisterTask(TASK_100MS, Swc_Kata002_Runnable_100ms, 100, "SWC_Kata002_100ms");
   ```

7. **Build and test**
   ```bash
   make autosar-run
   ```

## 🎓 Example Kata Workflow

### Day 1: FizzBuzz

**Problem:** Print numbers 1-100, but for multiples of 3 print "Fizz", multiples of 5 print "Buzz", both print "FizzBuzz".

**Implementation in AUTOSAR:**

```c
// Swc_FizzBuzz.c
void Swc_FizzBuzz_Runnable_10ms(void) {
    static uint32 number = 1;
    uint32 result;
    
    // FizzBuzz logic
    if (number % 15 == 0) {
        result = 0xFFFF; // FizzBuzz
    } else if (number % 3 == 0) {
        result = 0x0003; // Fizz
    } else if (number % 5 == 0) {
        result = 0x0005; // Buzz
    } else {
        result = number;
    }
    
    Rte_Write_SwcFizzBuzz_Output(result);
    
    if (++number > 100) number = 1;
}
```

### Day 2: String Reversal

**Problem:** Reverse a string.

**Implementation:**

```c
// Use a circular buffer or state machine
void Swc_StringReverse_Runnable_10ms(void) {
    uint32 char_in, char_out;
    static uint32 buffer[256];
    static uint32 write_idx = 0;
    
    Rte_Read_SwcStringReverse_CharIn(&char_in);
    
    if (char_in == 0) { // Null terminator - reverse
        for (int i = write_idx - 1; i >= 0; i--) {
            Rte_Write_SwcStringReverse_CharOut(buffer[i]);
        }
        write_idx = 0;
    } else {
        buffer[write_idx++] = char_in;
    }
}
```

## 🔧 Advanced Features

### Adding RTE Ports

Edit `Rte.h` to add new port definitions:

```c
// For your new kata
#define Rte_Read_SwcKata002_MyInput(data) \
    Rte_Read(2, 0, (void*)(data))

#define Rte_Write_SwcKata002_MyOutput(data) \
    Rte_Write(2, 0, (const void*)&(data))
```

Update `Rte.c` port mapping:

```c
static const Rte_PortMappingType port_mapping[] = {
    // ... existing mappings ...
    {2, 0, COM_SIGNAL_INPUT_A},   // Kata002 input
    {2, 0, COM_SIGNAL_OUTPUT_RESULT}, // Kata002 output
};
```

### Adding COM Signals

Edit `Com.h`:

```c
typedef enum {
    COM_SIGNAL_INPUT_A = 0,
    COM_SIGNAL_INPUT_B,
    COM_SIGNAL_OUTPUT_RESULT,
    COM_SIGNAL_MY_NEW_SIGNAL,  // Add here
    COM_SIGNAL_COUNT
} Com_SignalIdType;
```

## 📊 Testing and Coverage

### Unit Tests

Create tests in `test/autosar/`:

```c
// test/autosar/test_kata001.c
#include "Swc_Kata001.h"
#include <assert.h>

void test_addition(void) {
    // Mock RTE reads/writes
    // Test your kata logic
    assert(result == expected);
}
```

### Coverage Report

```bash
make autosar-coverage
# Opens: build/coverage/coverage.html
```

## 🎯 Learning Path

### Week 1: Basics
- ✅ Understand AUTOSAR layers (BSW, RTE, SWC)
- ✅ Implement 3 simple katas (addition, multiplication, etc.)
- ✅ Learn RTE communication patterns

### Week 2: Intermediate
- ⬜ State machines in SWCs
- ⬜ Multiple input/output ports
- ⬜ Inter-component communication

### Week 3: Advanced
- ⬜ Timing analysis
- ⬜ Error handling (DET)
- ⬜ Complex data structures

### Week 4: Mastery
- ⬜ Full CodeWars kata in AUTOSAR
- ⬜ Performance optimization
- ⬜ Real-time constraints

## 🐛 Debugging Tips

### Print Debug Info

```c
#include <stdio.h>

void Swc_MyKata_Runnable_10ms(void) {
    printf("[DEBUG] Input: %u\n", input);
    // Your logic
    printf("[DEBUG] Output: %u\n", output);
}
```

### GDB Debugging

```bash
make autosar-debug
gdb build/autosar/autosar_lab

(gdb) break Swc_Kata001_Runnable_10ms
(gdb) run
(gdb) print input1
```

### Timing Analysis

```c
#include "Os.h"

void Swc_MyKata_Runnable_10ms(void) {
    uint32 start = Os_GetTick();
    
    // Your logic
    
    uint32 duration = Os_GetTick() - start;
    printf("[TIMING] Execution: %u ms\n", duration);
}
```

## 📖 AUTOSAR Concepts Reference

### Component Types
- **Sensor SWC**: Reads hardware (via BSW)
- **Application SWC**: Business logic (your katas!)
- **Actuator SWC**: Controls hardware

### Communication Patterns
- **Sender-Receiver**: Asynchronous data exchange
- **Client-Server**: Synchronous service calls
- **Mode Management**: System state control

### Timing
- **10ms tasks**: Fast control loops
- **100ms tasks**: Monitoring, diagnostics
- **1000ms tasks**: Logging, statistics

## 🤝 Contributing Your Katas

Share your kata solutions:

```bash
# Create a branch for your kata
git checkout -b kata/fizzbuzz

# Add your files
git add src/autosar/swc/kata_003/

# Commit with description
git commit -m "Add FizzBuzz kata implementation"

# Push and create PR
git push origin kata/fizzbuzz
```

## 📚 Resources

- [AUTOSAR Classic Platform](https://www.autosar.org/)
- [CodeWars](https://www.codewars.com/) - Daily kata source
- Your repository issues - Ask questions!

## 🎉 Next Steps

1. **Run the example**: `make autosar-run`
2. **Explore the code**: Read through `Swc_Kata001.c`
3. **Create your first kata**: `make new-kata`
4. **Implement a CodeWars problem**: Start simple!
5. **Check coverage**: `make autosar-coverage`
6. **Iterate**: One kata per day!

---

**Happy Coding! 🚗💻**

Remember: The goal is to learn AUTOSAR architecture while practicing your coding skills. Don't worry about making it perfect—focus on understanding the layers and communication patterns!
