jmp main

twofour:
    push 24
    prnt                ; Print twenty-four to standard out
    ret

main:                   ; Main function
    push 3
    push 4
    add
    prnt
    call twofour 0

end:
    halt