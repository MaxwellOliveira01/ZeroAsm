SECTION TEXT
READ_AND_ADDONE: MACRO &A
READ &A
ADDONE &A
ENDMACRO
READ: MACRO &A
INPUT &A
ENDMACRO
ADDONE: MACRO &A
LOAD &A
ADD ONE
STORE &A
ENDMACRO
READ_AND_ADDONE NUM + 1
SECTION DATA
NUM: SPACE 2
ONE: CONST 1