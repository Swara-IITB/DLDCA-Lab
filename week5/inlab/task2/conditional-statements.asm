; db -> define byte
; dw -> define word (16 bits)
; dd -> define double word (32 bits)
; dq -> define quad word (64 bits)
section .data
    fizz_msg db "fizz"
    buzz_msg db "buzz"
    fizz_len equ 4
    buzz_len equ 4

section .bss
    input_buf resb 20  ; Reserve 20 bytes for input
    num     resq 1     ; 64-bit integer

section .text
    global _start ; essentially just means start here


_start:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; START OF YOUR CODE ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; Take in number as input from user
    ; You can do this using read(0, input_buffer, size) syscall, syscall number for read is 0
    ; Make sure your input buffer is stored in rsi :)
    mov rax, 0
    mov rdi, 0
    mov rsi, input_buf
    mov rdx, 20
    syscall
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; END OF YOUR CODE ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; The below code simply converts input string to a number, don't worry about it
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
    ; Now RAX contains the number entered (num)
    ; Here is the C code you need to implement in assembly:
    ; if (num % 3 == 0) {
    ;     print "fizz"; Use syscall write(1, fizz_msg, fizz_len), syscall number for write is 1
    ;}
    ; if (num % 5 == 0) {
    ;     print "buzz"; Use syscall write(1, buzz_msg, buzz_len), syscall number for write is 1
    ;}
    ; Modulus in asm can be done as follows:
    ; rax = num
    ; rcx = divisor 
    ; xor rdx, rdx  ; clear rdx for division
    ; div rcx       ; rax = num / divisor, rdx = num % divisor
    ; Conditional statements can be done using cmp to compare two operands and jnz/jz/je/jne/jg/jge/jl/jle instructions
    ; For example, if you wanted to check if a == b
    ; mov rax, a
    ; mov rbx, b
    ; cmp rax, rbx
    ; je .equal  ; if a == b, jump to .equal
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; START OF YOUR CODE ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov rbx, rax
    mov rcx, 3; rcx = 3
    xor rdx, rdx
    div rcx   ; rax = num/3 , rdx = num % 3
    cmp rdx, 0
    je .printFizz
    jmp .next

.printFizz:
    mov rax, 1
    mov rdi, 1
    mov rsi, fizz_msg
    mov rdx, 4
    syscall

.next:
    mov rax, rbx
    mov rcx, 5; rcx = 5
    xor rdx, rdx
    div rcx   ; rax = num/5 , rdx = num % 5
    cmp rdx, 0
    je .printBuzz
    jmp .end
    
.printBuzz:
    mov rax, 1
    mov rdi, 1
    mov rsi, buzz_msg
    mov rdx, 4
    syscall

.end:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; END OF YOUR CODE ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    mov rax, 60              ; syscall: exit
    xor rdi, rdi             ; exit code 0
    syscall
