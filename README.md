NFA-to-DFA
==========
1. Give nfa as an input:
    8
    0 0 2 8
    0 0 3 5
    4 0 0 0
    0 0 7 0
    0 6 0 0
    0 0 7 0
    0 0 2 8
    0 0 0 0
2. Program generates dfa as an output:
    DFA:
    St  a   b
    1   2   3
    2   2   3
    3   2   3
    
    Final states: 1, 2, 3,
