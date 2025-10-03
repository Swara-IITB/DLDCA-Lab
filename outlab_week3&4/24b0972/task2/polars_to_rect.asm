section .data

complex1:
    complex1_name db 'a'
    complex1_pad  db 7 dup(0)  
    complex1_real dq 1.0
    complex1_img  dq 2.5

complex2:
    complex2_name db 'b'
    complex2_pad  db 7 dup(0)  
    complex2_real dq 3.5
    complex2_img  dq 4.0

polar_complx:
    polar_complx_name db 'c'
    polar_complx_pad db 7 dup(0)
    polar_complx_mag dq 10.0
    polar_complx_ang dq 0.0001

fmt db "%s => %f %f", 10, 0     ;
label_polar2rect db "Testing polars to rectangular",0
label_exp db "Testing exp",0
label_sin db "Testing sin",0
label_cos db "Testing cos",0

;;;;;;;;;;;;;
six dq 6.0
two dq 2.0
one dq 1.0
temp dq 0.0
;;;; Fill other constants needed
twentyfour dq 24.0
onetwenty dq 120.0
seventwenty dq 720.0
fivezfourz dq 5040.0
;;;;;;;;;;;;;

temp_cmplx:
    temp_name db 'r'
    temp_pad  db 7 dup(0)
    temp_real dq 0.0
    temp_img  dq 0.0

section .text
    default rel
    extern print_cmplx,print_float
    global main

main:
    push rbp
    ; --- Test: Polar to Rectangular ---
    lea rdi, [polar_complx]         ; pointer to input polar struct
    lea rsi, [temp_cmplx]     ; pointer to output rect struct
    
    call polars_to_rect

    lea rdi, [label_polar2rect]
    lea rsi, [temp_cmplx]
    call print_cmplx          ; should show converted rectangular form

    ; --- Test: exp ---
    movsd xmm0, [two]
    mov rdi, 0x6

    call exp

    movsd [temp],xmm0 
    lea rdi, [label_exp]
    lea rsi , [temp]
    call print_float

    ; --- Test: sin ---
    movsd xmm0, [two]

    call sin

    movsd [temp],xmm0 
    lea rdi, [label_sin]
    lea rsi , [temp]
    call print_float

    ; --- Test: cos ---
    movsd xmm0, [two]
    call cos

    movsd [temp],xmm0 
    lea rdi, [label_cos]
    lea rsi , [temp]
    call print_float

    mov     rax, 60         ; syscall: exit
    xor     rdi, rdi        ; status 0
    syscall


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; FILL FUNCTIONS BELOW ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; -----------------------------------
polars_to_rect:
    movsd xmm0, [rdi+16]
    push rdi
    push rsi
    call cos
    pop rsi 
    pop rdi
    movsd xmm1, [rdi+8]
    mulsd xmm1, xmm0
    movsd [rsi+8], xmm1
    movsd xmm0, [rdi+16]
    push rdi
    push rsi
    call sin
    pop rsi
    pop rdi
    movsd xmm1, [rdi+8]
    mulsd xmm1, xmm0
    movsd [rsi+16], xmm1
    ret
;-------------------------------------------------
exp:
    movsd xmm1, [one];temp
    xor r8, r8
exp_loop:
    mulsd xmm1, xmm0
    inc r8
    cmp r8, rdi
    jl exp_loop
    movsd xmm0, xmm1

    ret
;-------------------------------------------------
sin:
    push rdi

    movsd xmm1, xmm0; xmm1->answer, xmm0->theta
    sub rsp, 32
    movsd [rsp], xmm0; 
    movsd [rsp+16], xmm1
    mov rdi, 0x3
    call exp
    movsd xmm1, [rsp+16]
    movsd xmm2, [six]
    divsd xmm0, xmm2
    subsd xmm1, xmm0
    movsd [rsp+16], xmm1
    movsd xmm0, [rsp]
    mov rdi, 0x5
    call exp
    movsd xmm1, [rsp+16]
    movsd xmm2, [onetwenty]
    divsd xmm0, xmm2
    addsd xmm1, xmm0
    movsd [rsp+16], xmm1
    movsd xmm0, [rsp]
    mov rdi, 0x7
    call exp
    movsd xmm1, [rsp+16]
    movsd xmm2, [fivezfourz]
    divsd xmm0, xmm2
    subsd xmm1, xmm0
    movsd xmm0, xmm1
    add rsp, 32

    pop rdi
    ret

cos:
    push rdi

    movsd xmm1, [one]; xmm1->answer, xmm0->theta
    sub rsp, 32
    movsd [rsp], xmm0; 
    movsd [rsp+16], xmm1
    mov rdi, 0x2
    call exp
    movsd xmm1, [rsp+16]
    movsd xmm2, [two]
    divsd xmm0, xmm2
    subsd xmm1, xmm0
    movsd [rsp+16], xmm1
    movsd xmm0, [rsp]
    mov rdi, 0x4
    call exp
    movsd xmm1, [rsp+16]
    movsd xmm2, [twentyfour]
    divsd xmm0, xmm2
    addsd xmm1, xmm0
    movsd [rsp+16], xmm1
    movsd xmm0, [rsp]
    mov rdi, 0x6
    call exp
    movsd xmm1, [rsp+16]
    movsd xmm2, [seventwenty]
    divsd xmm0, xmm2
    subsd xmm1, xmm0
    movsd xmm0, xmm1
    add rsp, 32

    pop rdi
    ret
;-------------------------------------------------
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; CODE ENDS HERE ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;