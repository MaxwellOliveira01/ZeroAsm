SECTION TEXT
BEGIN : MOD1 ;comentario1
MOD2    : EXTERN; comentario 2
Public L2
Public OLD_DATA
    Public NEW_DATA
 Public TMP_DATA

;comentario 3
TRES: COPY   DOIS, TMP_DATA
INPUT OLD_DATA
 LOAD OLD_DATA
    jmp mod2; comentario 4
                L2: STOP    ;comentario 5
   END
        SECTION DATA
DOIS: CONST 2
OLD_DATA: SPACE             ;;;;;;; comentario 6

;comentario 7

NEW_DATA: SPACE;        ;comentario7
TMP_DATA: SPACE;comentario8;
ESPACOS: SPACE 10