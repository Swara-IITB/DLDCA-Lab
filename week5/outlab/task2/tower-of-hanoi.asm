section .data
    shifted_disk db "Shifted disk "
    from_str db " from "
    to_str db " to "
    a_rod db 'A'
    b_rod db 'B'
    c_rod db 'C'
    newline db 10
    shifted_len equ 13
    from_len equ 6
    to_len equ 4
    buffer db 100 dup(0) ; Output buffer for result string

section .bss
    input_buf resb 20  ; Reserve 20 bytes for input
    num resq 1         ; 64-bit integer

section .text
    global printNum
    global hanoi
    global _start 
    global printFromAndTo

printNum:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Start of your code ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Write code to print an arbitary number stored in rax
    push rbp
    push rsp
    push rbx
    push r12
    push r13
    push r14
    push r15

    mov rbx, rax
    mov r13, 99
    mov rsi, buffer
.whileBegin:
    cmp rax, 0
    jle .whileEnd
    mov rbp, 10
    xor rdx, rdx
    div rbp
    add dl, '0'
    mov [rsi+r13], dl
    dec r13
    jmp .whileBegin
.whileEnd:
    mov rax, 1
    mov rdi, 1
    lea rsi, [buffer + r13 + 1]
    mov rdx, 99
    sub rdx, r13
    syscall
    mov rax, rbx
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rsp
    pop rbp
    ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  End of your code  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

printFromAndTo:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Start of your code ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Write code to print " from " *rax " to " *rdi
    push rbp
    push rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    
    mov r12, rax
    mov r13, rdi

    mov rax, 1
    mov rdi, 1
    mov rsi, from_str
    mov rdx, from_len
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, r12
    mov rdx, 1
    syscall
    
    mov rax, 1
    mov rdi, 1
    mov rsi, to_str
    mov rdx, to_len
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, r13
    mov rdx, 1
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rsp
    pop rbp

    ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  End of your code  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
hanoi:
    push rbp
    push rsp
    push rbx
    push r12
    push r13
    push r14
    push r15 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Start of your code ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;; C code for function
;;;; void hanoi(int n, char from, char to, char aux) {
;;;;     if (n == 1) {
;;;;         printf("Shifted disk 1 from %c to %c\n", from, to);
;;;;         return;
;;;;     }
;;;;     hanoi(n - 1, from, aux, to);
;;;;     printf("Shifted disk %d from %c to %c\n", n, from, to);
;;;;     hanoi(n - 1, aux, to, from);
;;;; }
    mov r12, rdi ; r12 -> n
    mov r13, rsi ; r13 -> from
    mov r14, rdx ; r14 -> to
    mov r15, rcx ; r15 -> aux

    cmp r12, 1
    je .pret
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11
    
    mov rdi, r12
    dec rdi
    mov rsi, r13
    mov rdx, r15
    mov rcx, r14
    call hanoi

    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi

    mov rax, 1
    mov rdi, 1
    mov rsi, shifted_disk
    mov rdx, shifted_len
    syscall

    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11

    mov rax, r12
    call printNum

    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11
    
    mov rax, r13
    mov rdi, r14
    call printFromAndTo

    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi

    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11
    
    mov rdi, r12
    dec rdi
    mov rsi, r15
    mov rdx, r14
    mov rcx, r13
    call hanoi

    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    jmp .return
.pret:

    mov rax, 1
    mov rdi, 1
    mov rsi, shifted_disk
    mov rdx, shifted_len
    syscall

    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11

    mov rax, 1
    call printNum

    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11
    
    mov rax, r13
    mov rdi, r14
    call printFromAndTo

    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    jmp .return

.return:
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rsp
    pop rbp

    ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  End of your code  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_start:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Start of your code ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Write code to take in number as input, then call hanoi(num, 'A','B','C')

    mov rax, 0
    mov rdi, 0
    mov rsi, input_buf
    mov rdx, 20
    syscall

    mov rsi, input_buf  ; rsi points to buffer
    xor rax, rax        ; accumulator = 0

.convert1:
    movzx rcx, byte [rsi] ; load byte
    cmp rcx, 10           ; check for newline
    je .done1
    sub rcx, '0'          ; convert ASCII to digit
    imul rax, rax, 10
    add rax, rcx
    inc rsi
    jmp .convert1

.done1:
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11
    
    mov rdi, rax
    mov rsi, a_rod
    mov rdx, b_rod
    mov rcx, c_rod
    call hanoi

    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  End of your code  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov     rax, 60         ; syscall: exit
    xor     rdi, rdi        ; status 0
    syscall