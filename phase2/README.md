# SimpleLang Compiler - Phase 2

A custom programming language compiler with Arabic-style keywords, featuring:
- **Symbol Table** with scope management
- **Quadruple Generation** (Three-Address Code)
- **Semantic Analysis** with type checking
- **Error Recovery** for graceful handling of syntax errors
- **GUI Interface** for easy compilation

## Language Features

### Data Types
| Keyword | Type |
|---------|------|
| `rakam` | Integer |
| `kasr` | Float |
| `kalam` | String |
| `mantiq` | Boolean |

### Boolean Values
- `sa7` - True
- `ghalat` - False

### Keywords
| Keyword | Meaning |
|---------|---------|
| `sabit` | Constant declaration |
| `law` | If statement |
| `walla` | Else clause |
| `tool ma` | While loop |
| `lef` | For loop |
| `karrar` | Do-while loop |
| `le7ad` | Until |
| `shoghla` | Function declaration |
| `ragga3` | Return statement |
| `etba3` | Print statement |
| `ekhtar` | Switch statement |
| `7ala` | Case clause |
| `asasya` | Default clause |
| `ekhla3` | Break statement |
| `kamel` | Continue statement |

### Operators
- **Arithmetic:** `+`, `-`, `*`, `/`, `%`, `^`
- **Comparison:** `<`, `>`, `<=`, `>=`, `==`, `!=`
- **Logical:** `&&`, `||`, `!`
- **Assignment:** `=`, `+=`, `-=`, `*=`, `/=`
- **Increment/Decrement:** `++`, `--`

## Building the Compiler

### Prerequisites
- GCC compiler
- Flex (lexical analyzer generator)
- Bison (parser generator)
- Python 3 (for GUI)
- tkinter (Python GUI library)

### On Linux/macOS
```bash
cd phase2
make
```

### On Windows (with MinGW)
```bash
cd phase2
make windows
```

## Running the Compiler

### Command Line
```bash
./compiler input.sl
```

### GUI Mode
```bash
python compiler_gui.py
```
Or on Windows:
```bash
python compiler_gui.py
```

## Example Program

```
// Variable declarations
rakam x = 10;
kasr pi = 3.14;
kalam msg = "Hello!";

// Constant
sabit rakam MAX = 100;

// Function
shoghla rakam add(rakam a, rakam b) {
    ragga3 a + b;
}

// Control flow
law (x < 20) {
    etba3 "x is small";
} wella {
    etba3 "x is large";
}

// Loop
lef (rakam i = 0; i < 5; i++) {
    etba3 i;
}

// Function call
rakam result = add(5, 3);
etba3 result;
```

## Output Files

- **symbols.txt** - Symbol table contents
- **Console output** - Quadruples and compilation summary

## Project Structure

```
phase2/
├── simplelang.l      # Lexer specification (Flex)
├── simplelang.y      # Parser specification (Bison)
├── val.h             # Value types definition
├── parameter.h       # Function parameter structures
├── symbol_table.h    # Symbol table header
├── symbol_table.c    # Symbol table implementation
├── quadruples.h      # Quadruples header
├── quadruples.c      # Quadruples implementation
├── semantic.h        # Semantic analyzer header
├── semantic.c        # Semantic analyzer implementation
├── compiler_gui.py   # GUI application
├── Makefile          # Build configuration
├── test1.sl          # Test: Basic declarations
├── test2.sl          # Test: Control flow
├── test3.sl          # Test: Functions
├── test4.sl          # Test: Semantic errors
└── test5.sl          # Test: Comprehensive example
```

## Phase 2 Features

### 1. Symbol Table
- Hash-based implementation with collision handling
- Scope management (nested scopes supported)
- Tracks variable usage and initialization
- Function parameter storage

### 2. Quadruple Generation
Generated three-address code format: `(op, arg1, arg2, result)`

Example:
```
(ADD, x, y, t0)
(ASSIGN, t0, _, z)
(JMP_FALSE, t1, _, L0)
```

### 3. Semantic Analysis
- Type checking for assignments and expressions
- Function call argument validation
- Constant modification detection
- Unused variable warnings
- Uninitialized variable warnings
- Break/continue context validation

### 4. Error Handling
- Syntax error recovery (continues parsing after errors)
- Detailed error messages with line numbers
- Compilation summary showing error/warning counts

## Authors
SimpleLang Compiler - Compiler Construction Project

## License
Educational use only.
