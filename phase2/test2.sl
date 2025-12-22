// SimpleLang Test File 2 - Control Flow
// Tests: If-else, while, for, do-while, switch

rakam x = 10;
rakam y = 20;

// If-else statement
law (x < y) {
    etba3 "x is less than y";
} wella {
    etba3 "x is greater or equal to y";
}

// Nested if
law (x > 0) {
    law (x < 100) {
        etba3 "x is between 0 and 100";
    }
}

// While loop
rakam counter = 0;
tool ma (counter < 5) {
    etba3 counter;
    counter = counter + 1;
}

// For loop
lef (rakam i = 0; i < 3; i++) {
    etba3 i;
}

// Do-while loop
rakam n = 0;
karrar {
    etba3 n;
    n = n + 1;
} tool ma (n < 3);

// Switch statement
rakam choice = 2;
ekhtar (choice) {
    7ala 1:
        etba3 "Choice is 1";
        ekhla3;
    7ala 2:
        etba3 "Choice is 2";
        ekhla3;
    7ala 3:
        etba3 "Choice is 3";
        ekhla3;
    asasya:
        etba3 "Unknown choice";
}

etba3 "Control flow tests completed!";
