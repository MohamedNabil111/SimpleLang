// SimpleLang Test File 4 - Semantic Error Tests
// This file contains intentional errors to test semantic analysis

// Error: Using undefined variable
// rakam a = undefined_var;

// Error: Redeclaration in same scope
rakam x = 10;
// rakam x = 20;  // Uncomment to test redeclaration error

// Warning: Unused variable
rakam unused_var = 100;

// Error: Type mismatch
// kalam str = 123;  // Uncomment to test type mismatch

// Error: Modifying constant
sabit rakam CONST_VAL = 50;
// CONST_VAL = 60;  // Uncomment to test constant modification error

// Warning: Uninitialized variable
rakam uninitialized;
// etba3 uninitialized;  // Uncomment to test uninitialized warning

// Test scope - same name in different scopes is OK
{
    rakam x = 30;  // New x in inner scope
    etba3 x;
}
etba3 x;  // Original x

etba3 "Semantic error tests - check the errors tab!";
