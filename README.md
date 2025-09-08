# ⚡ ThisFunc Interpreter

## ℹ️ Overview
This project implements an **interpreter** for the functional programming language **ThisFunc**.  
The interpreter can run in **interactive mode** (REPL) or execute code from files, evaluating expressions and printing results.  

The project is developed mainly using **Data Structures and Programming**, which ensures clear program flow and maintainability.
Used data structures: stack, linked list, hash table.

---

## ✨ Language Features
- **Literals** → only real numbers  
- **Expressions** → nested function calls  
- **Built-in functions**:
  - Arithmetic: `add`, `sub`, `mul`, `div`, `pow`, `sqrt`  
  - Trigonometry: `sin`, `cos`  
  - Logic: `eq`, `le`, `nand`  
- **User-defined functions** with parameters (`#0`, `#1`, …)  
- **Special functions**:
  - `if(test, if-true, if-false)`  
  - `list(arg1, arg2, …)`  
  - `head(list)`  
  - `tail(list)`  
  - `map(function, list)`  
  - `filter(function, list)`  
- **Supports recursion** in function definitions  

---

## 🛠 Examples
```text
add(3, 7)
> 10

doubleArg <- add(#0, #0)
doubleArg(5)
> 10

sumSqr <- add(mul(#0, #0), mul(#1, #1))
sumSqr(5, 10)
> 125

myList <- list(1, 2, 3, 4)
myList()
> [1, 2, 3, 4]

fact <- if(eq(#0, 0), 1, mul(#0, fact(sub(#0, 1))))
fact(5)
> 120
```
---
## 🚀 Usage
Clone the repository:
  `git clone https://github.com/StefanNikolov18/thisFunc-interpreter.git`  

---

## Extra
 📖 Full documentation is available in `Documentation/html/index.html`.
