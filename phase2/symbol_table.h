/**
 * SimpleLang Compiler - Phase 2
 * Symbol Table Header
 * 
 * Implements a hash-based symbol table with scope support.
 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "val.h"
#include "parameter.h"

#define TABLE_SIZE 101

// File for symbol table output
extern FILE *SYMTAB_FILE;

// Symbol types
typedef enum {
    SYM_VARIABLE,
    SYM_CONSTANT,
    SYM_FUNCTION
} SymbolType;

// Symbol structure
typedef struct Symbol {
    char *name;                   // Symbol name
    val *value;                   // Value and type info
    SymbolType sym_type;          // Variable, constant, or function
    struct Symbol *next;          // Hash chain
    int param_count;              // For functions: parameter count
    struct Parameter *params;     // For functions: parameter list
    bool is_used;                 // Has symbol been used?
    bool is_initialized;          // Has variable been initialized?
    int line_declared;            // Line number where declared
} Symbol;

// Symbol table structure (scope)
typedef struct SymbolTable {
    Symbol *table[TABLE_SIZE];    // Hash table buckets
    struct SymbolTable *parent;   // Parent scope
    int scope_level;              // Scope depth (0 = global)
    char *scope_name;             // Name for debugging
} SymbolTable;

// ============= Symbol Table Functions =============

// Create a new symbol table (scope)
SymbolTable* create_symbol_table(SymbolTable *parent);

// Hash function for symbol names
unsigned int hash(const char *name);

// Insert a symbol into the table
Symbol* insert_symbol(SymbolTable *table, 
                      const char *name, 
                      val *value, 
                      SymbolType sym_type,
                      int param_count,
                      Parameter *params,
                      int line_num);

// Lookup a symbol (searches current and parent scopes)
Symbol* lookup_symbol(SymbolTable *table, const char *name);

// Check if symbol exists in current scope only
bool is_symbol_in_current_scope(SymbolTable *table, const char *name);

// Free a symbol table and its symbols
void free_symbol_table(SymbolTable *table);

// Print symbol table to file
void print_symbol_table(SymbolTable *table);

// Print symbol table to stdout
void print_symbol_table_stdout(SymbolTable *table);

// ============= Parameter Functions =============

// Create a new parameter
Parameter* create_param(const char *name, val *value);

// Append a parameter to a list
Parameter* append_param(Parameter *head, Parameter *new_param);

// Free parameter list
void free_params(Parameter *params);

// Count parameters
int count_params(Parameter *params);

#endif // SYMBOL_TABLE_H
