            jmp main

factorial:
            pop
            dup
            push 1  
            sub
            dup
            push 2
            lt
            jt return
            call factorial 1
return:
            mul
            ret

main:
            push 10
            call factorial 1
            prnt
            halt