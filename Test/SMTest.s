jmp main

twofour:
    push 24
    prnt
    jmp end

main:
    push 3
    push 4
    add
    prnt
    jmp twofour

end:
    halt