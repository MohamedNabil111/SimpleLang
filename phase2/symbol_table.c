/**
 * SimpleLang Compiler - Phase 2
 * Symbol Table Implementation
 */

#include "symbol_table.h"

// Global file pointer for symbol table output
FILE *SYMTAB_FILE = NULL;

// Hash function (djb2 algorithm)
unsigned int hash(const char *name) {
    unsigned long h = 5381;
    int c;
    while ((c = *name++)) {
        h = ((h << 5) + h) + c;
    }
    return (unsigned int)(h % TABLE_SIZE);
}

// Create a new symbol table
SymbolTable* create_symbol_table(SymbolTable *parent) {
    SymbolTable *table = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!table) {
        fprintf(stderr, "Error: Unable to allocate SymbolTable\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->table[i] = NULL;
    }
    
    table->parent = parent;
    table->scope_level = parent ? parent->scope_level + 1 : 0;
    table->scope_name = NULL;
    
    return table;
}

// Insert a symbol into the table
Symbol* insert_symbol(SymbolTable *table, 
                      const char *name, 
                      val *value, 
                      SymbolType sym_type,
                      int param_count,
                      Parameter *params,
                      int line_num) {
    if (!table || !name || !value) {
        fprintf(stderr, "Error: Null pointer passed to insert_symbol\n");
        return NULL;
    }
    
    // Check for duplicate in current scope
    if (is_symbol_in_current_scope(table, name)) {
        fprintf(stderr, "Semantic Error: '%s' already declared in this scope (line %d)\n", 
                name, line_num);
        free_val(value);
        if (sym_type == SYM_FUNCTION) {
            free_params(params);
        }
        return NULL;
    }
    
    // Allocate new symbol
    Symbol *new_symbol = (Symbol*)malloc(sizeof(Symbol));
    if (!new_symbol) {
        fprintf(stderr, "Error: Memory allocation failed for Symbol\n");
        free_val(value);
        if (sym_type == SYM_FUNCTION) {
            free_params(params);
        }
        return NULL;
    }
    
    // Fill in fields
    new_symbol->name = strdup(name);
    new_symbol->value = value;
    new_symbol->sym_type = sym_type;
    new_symbol->param_count = (sym_type == SYM_FUNCTION) ? param_count : 0;
    new_symbol->params = (sym_type == SYM_FUNCTION) ? params : NULL;
    new_symbol->is_used = false;
    new_symbol->is_initialized = (sym_type == SYM_CONSTANT);
    new_symbol->line_declared = line_num;
    
    // Insert at head of bucket
    unsigned int idx = hash(name);
    new_symbol->next = table->table[idx];
    table->table[idx] = new_symbol;
    
    return new_symbol;
}

// Lookup a symbol (searches current and parent scopes)
Symbol* lookup_symbol(SymbolTable *table, const char *name) {
    if (!table || !name) return NULL;
    
    for (SymbolTable *cur = table; cur != NULL; cur = cur->parent) {
        unsigned int idx = hash(name);
        for (Symbol *sym = cur->table[idx]; sym != NULL; sym = sym->next) {
            if (strcmp(sym->name, name) == 0) {
                return sym;
            }
        }
    }
    return NULL;
}

// Check if symbol exists in current scope only
bool is_symbol_in_current_scope(SymbolTable *table, const char *name) {
    if (!table || !name) return false;
    
    unsigned int idx = hash(name);
    for (Symbol *sym = table->table[idx]; sym != NULL; sym = sym->next) {
        if (strcmp(sym->name, name) == 0) {
            return true;
        }
    }
    return false;
}

// Helper to get symbol type as string
static const char* sym_type_to_string(SymbolType st) {
    switch (st) {
        case SYM_VARIABLE: return "Variable";
        case SYM_CONSTANT: return "Constant";
        case SYM_FUNCTION: return "Function";
        default:           return "Unknown";
    }
}

// Print symbol table to file
void print_symbol_table(SymbolTable *table) {
    if (!SYMTAB_FILE || !table) return;
    
    fprintf(SYMTAB_FILE, "\n=== Scope Level %d ===\n", table->scope_level);
    fprintf(SYMTAB_FILE, "%-20s %-12s %-12s %-10s %-10s %-10s\n",
            "Name", "Type", "DataType", "SymType", "Used", "Initialized");
    fprintf(SYMTAB_FILE, "--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (Symbol *sym = table->table[i]; sym != NULL; sym = sym->next) {
            fprintf(SYMTAB_FILE, "%-20s %-12s %-12s %-10s %-10s %-10s\n",
                    sym->name,
                    type_to_string(sym->value->type),
                    sym_type_to_string(sym->sym_type),
                    sym->sym_type == SYM_FUNCTION ? "Function" : "Symbol",
                    sym->is_used ? "Yes" : "No",
                    sym->is_initialized ? "Yes" : "No");
            
            // Print function parameters if any
            if (sym->sym_type == SYM_FUNCTION && sym->params) {
                fprintf(SYMTAB_FILE, "    Parameters (%d): ", sym->param_count);
                Parameter *p = sym->params;
                while (p) {
                    fprintf(SYMTAB_FILE, "%s:%s", p->name, type_to_string(p->value->type));
                    if (p->next) fprintf(SYMTAB_FILE, ", ");
                    p = p->next;
                }
                fprintf(SYMTAB_FILE, "\n");
            }
        }
    }
}

// Print symbol table to stdout
void print_symbol_table_stdout(SymbolTable *table) {
    if (!table) return;
    
    printf("\n=== Scope Level %d ===\n", table->scope_level);
    printf("%-20s %-12s %-12s %-10s %-10s\n",
           "Name", "DataType", "SymType", "Used", "Init");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (Symbol *sym = table->table[i]; sym != NULL; sym = sym->next) {
            printf("%-20s %-12s %-12s %-10s %-10s\n",
                   sym->name,
                   type_to_string(sym->value->type),
                   sym_type_to_string(sym->sym_type),
                   sym->is_used ? "Yes" : "No",
                   sym->is_initialized ? "Yes" : "No");
        }
    }
}

// Free a symbol table
void free_symbol_table(SymbolTable *table) {
    if (!table) return;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *cur = table->table[i];
        while (cur) {
            Symbol *tmp = cur;
            cur = cur->next;
            
            // Warnings for unused symbols
            if (tmp->sym_type == SYM_VARIABLE && !tmp->is_used) {
                fprintf(stderr, "Warning: Variable '%s' declared but not used.\n", tmp->name);
            }
            if (tmp->sym_type == SYM_FUNCTION && !tmp->is_used) {
                fprintf(stderr, "Warning: Function '%s' declared but not called.\n", tmp->name);
            }
            if (tmp->sym_type == SYM_VARIABLE && !tmp->is_initialized) {
                fprintf(stderr, "Warning: Variable '%s' declared but not initialized.\n", tmp->name);
            }
            
            free(tmp->name);
            free_val(tmp->value);
            if (tmp->sym_type == SYM_FUNCTION && tmp->params) {
                free_params(tmp->params);
            }
            free(tmp);
        }
    }
    
    if (table->scope_name) free(table->scope_name);
    free(table);
}

// Create a new parameter
Parameter* create_param(const char *name, val *value) {
    Parameter *p = (Parameter*)malloc(sizeof(Parameter));
    if (!p) {
        perror("malloc failed for Parameter");
        exit(EXIT_FAILURE);
    }
    p->name = strdup(name);
    p->value = value;
    p->next = NULL;
    return p;
}

// Append a parameter to a list
Parameter* append_param(Parameter *head, Parameter *new_param) {
    if (!head) return new_param;
    
    Parameter *cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = new_param;
    return head;
}

// Free parameter list
void free_params(Parameter *params) {
    while (params) {
        Parameter *tmp = params;
        params = params->next;
        free(tmp->name);
        free_val(tmp->value);
        free(tmp);
    }
}

// Count parameters
int count_params(Parameter *params) {
    int count = 0;
    while (params) {
        count++;
        params = params->next;
    }
    return count;
}
