LALR parser
===========

    An LALR parser or Look-Ahead LR parser is a simplified version of a Canonical LR parser

    This tool takes BNF grammar as input and produces a LALR parsing table. Then any expression can be checked
    against the given grammar
    
    This tool displays following attributes of given BNF grammar :
        1. Terminals and Non Terminals
        2. First
        3. LR(1) states
        4. LALR states
        5. Parsing Table
        6. Evaluation table for each expression

    Following packages are required to run the tool:
        1. Python 3 or above
        2. PyQt4
