jmp main

twofour:
    push 24
    prnt
    ret

main:
    push 3
    push 4
    add
    prnt
    call 2 0

end:
    halt