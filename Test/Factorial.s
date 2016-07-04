            jmp main
factorial:
            load 0              ; 10
            dup                 ; 10 10
            push 1              ; 10 10 1
            sub                 ; 10 9
            dup                 ; 10 9 9
            push 2              ; 10 9 9 2
            lt                  ; 10 9 0
            jt factorial_ret    ; 10 9
            push 1              ; 10 9 1
            call factorial
factorial_ret:
            mul
            ret

main:
            push 10
            push 1
            call factorial
            prnt
            halt