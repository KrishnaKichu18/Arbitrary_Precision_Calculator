# 🧮 APC – Arbitrary Precision Calculator

**Developer:** Krishna M  
**Date:** 31 October 2025  
**Language:** C  
**Type:** System-Level Project  

---

## 📘 Overview

The **Arbitrary Precision Calculator (APC)** is a C-based implementation of large number arithmetic that overcomes the size limitations of standard integer data types.  
It performs **digit-by-digit operations** using **doubly linked lists**, allowing computations on numbers of *virtually unlimited length*.

This project demonstrates **low-level data structure design**, **modular architecture**, and **dynamic memory management** — a pure C implementation of big-integer arithmetic.

---

## ⚙️ Features

- ✅ Supports **Addition, Subtraction, Multiplication, Division, Modulus, and Power**
- ✅ Handles **numbers of any size** (limited only by system memory)
- ✅ Maintains **correct sign behavior** for all operations
- ✅ Includes **division-by-zero protection**
- ✅ Clean and **formatted output display**
- ✅ Modular design with reusable components (`addition.c`, `division.c`, etc.)
- ✅ Written entirely in **ANSI C**, no external libraries

---

## 🧩 Project Structure

APC_Project/  
├── main.c — Driver program: argument parsing, sign logic, and operation dispatcher  
├── addition.c — Addition of large numbers  
├── subtraction.c — Subtraction of large numbers  
├── multiplication.c — Classical long multiplication implementation  
├── division.c — Division and modulus using repeated subtraction  
├── power.c — Exponentiation via repeated multiplication  
├── Common.c — Shared utilities, validation, and list operations  
├── apc.h — Common header for type definitions and function prototypes  
└── Makefile — (Optional) For compilation automation  

---

## 🧠 Core Concepts

- **Linked List Arithmetic:** Each number is stored as a doubly linked list of digits (MSD → LSD).  
- **Carry & Borrow Propagation:** Implemented manually for accurate arithmetic.  
- **Dynamic Memory Management:** No static limits; memory is allocated per digit.  
- **Sign Handling:** Managed exclusively in `main.c` for modular arithmetic logic.  
- **Formatted Output:** Results printed in aligned column format.

---

## 🧪 Usage

### 🔹 Compilation
**Command:**
```
gcc main.c addition.c subtraction.c multiplication.c division.c power.c Common.c -o apc
```

### 🔹 Execution
**Run:**
```
./apc <number1> <operator> <number2>
```

### Example Output
```
       99999
x      99999
------------
= 9999800001
```

## 🧮 Supported Operators

| Operator | Operation      | Example              | Result  |
|-----------|----------------|----------------------|----------|
| `+` | Addition | `12 + 88` | `100` |
| `-` | Subtraction | `100 - 75` | `25` |
| `x` | Multiplication | `25 x 25` | `625` |
| `/` | Division | `10 / 3` | `3` |
| `%` | Modulus | `10 % 3` | `1` |
| `^` | Power | `2 ^ 10` | `1024` |

---

## 🚨 Error Handling

- Invalid input format  
- Non-numeric arguments  
- Division by zero  
- Memory allocation failure  

Each error is gracefully handled with user-friendly messages.

---

## 🧾 Example Demonstration
```
./apc -12345 + +67890
```


---

## 📂 Future Enhancements

- Implement **Exponentiation by Squaring** for faster power computation  
- Add **file-based input/output** for larger datasets  
- Include **floating-point support** (via scaled integer math)  
- Develop a **graphical or terminal-based interface**

---

## 🧑‍💻 Author Notes

This project was designed to test precision arithmetic using pure data-structure logic, focusing on:
- Memory safety  
- Algorithmic correctness  
- Modular organization  
- Aesthetic output formatting  

Meticulously engineered — because sometimes, *even numbers deserve perfection*.

---

## 🪪 License

This project is open for academic and educational use.  
Feel free to fork, improve, and learn from it — credit is appreciated.
