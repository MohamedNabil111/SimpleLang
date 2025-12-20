{
    rakam x = 10;
    rakam y = 20;
    
    law (x < y) {
        etba3 x;
    } law la2 yb2a {
        etba3 y;
    }
    
    tool ma (x < y) {
        x = x + 1;
    }
    
    etba3 x;
}
