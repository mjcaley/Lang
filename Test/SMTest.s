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
    call twofour 0

end:
    halt