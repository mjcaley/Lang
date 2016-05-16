            jmp main
factorial:
            pop
            dup
            push 1  
            sub
            dup
            push 2
            lt
            jf again
            jmp done
again:
            call factorial 1
done:
            mul
            ret

main:
            push 5
            call factorial 1
            prnt

end:
            halt