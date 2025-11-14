# AUTOSAR-like Example (C + MinGW + Makefile)
This project is a lightweight AUTOSAR-style architecture implemented in C.
It simulates the interaction between:

- **SWC (Software Components)**
- **RTE (Runtime Environment)**
- **BSW (Basic Software)** — specifically a simplified NvM module
- A small **main application** to run the example
- **Unit tests** using Acutest

The goal is to provide a practical environment for learning AUTOSAR concepts without needing a full toolchain or generators.

---

# Architecture Overview
The architecture mimics the AUTOSAR layered approach:

```
                          +----------------------+
                          |      SpeedSensor     |
                          |----------------------|
                          |  - Reads HW speed    |
                          |  - Calls RTE_Write() |
                          +----------+-----------+
                                     |
                                     | RTE_Write(SpeedValue)
                                     v
                   +-------------------------------+
                   |              RTE              |
                   |-------------------------------|
                   |  - Buffers SpeedValue         |
                   |  - Provides RTE_Read()        |
                   |  - Provides RTE_NvmRead/Write |
                   +--------+------------+---------+
                            |            |
                RTE_Read()  |            |  RTE_NvmRead/Write()
                            v            v
                  +----------------+   +-----------------+
                  | SpeedDisplay   |   |     NvM         |
                  |----------------|   |-----------------|
                  | - Reads speed  |   | - Load/store    |
                  |   via RTE      |   |   values        |
                  | - Shows output |   +--------+--------+
                  +----------------+           |
                                               | Uses
                                               v
                                         +-----------+
                                         |  Flash    |
                                         |-----------|
                                         | Persistent|
                                         |  Storage  |
                                         +-----------+


```


