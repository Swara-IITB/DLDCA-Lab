.data
CONTROL: .word32 0x10000
DATA:    .word32 0x10008

prompt:  .asciiz "Enter n to compute Fibonacci(n): "
result_msg: .asciiz "Fibonacci number: "
nl:      .asciiz "\n"

        .text
        ; Load MMIO register addresses
        lwu   $t9, CONTROL($zero)   ; $t9 = CONTROL address
        lwu   $t8, DATA($zero)      ; $t8 = DATA address

        ; Print prompt
        daddi $v0, $zero, 4         ; 4 = print string
        daddi $a0, $zero, prompt
        sd    $a0, 0($t8)           
        sd    $v0, 0($t9)

        ; Read n 
        daddi $v0, $zero, 8         ; 8 = read integer
        sd    $v0, 0($t9)
        ld    $s0, 0($t8)           ; $s0 = n

        ; Read n 
        daddi $v0, $zero, 8         ; 8 = read integer
        sd    $v0, 0($t9)
        ld    $s5, 0($t8)           ; $s5 = unrolling factor

        ; Compute Fibonacci(n) 
        ; F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)
        
        daddi $s1, $zero, 0         ; prev = 0
        daddi $s2, $zero, 1         ; curr = 1
        daddi $s3, $zero, 0         ; i = 0 

        daddi $s6, $zero, 0
        beq   $s5, $s6, fib_loop
        daddi $s6, $zero, 1
        beq   $s5, $s6, fib_loop1
        daddi $s6, $zero, 2
        beq   $s5, $s6, fib_loop2
        daddi $s6, $zero, 3
        beq   $s5, $s6, fib_loop3

fib_loop:
        beq   $s3, $s0, fib_done    ; if i == n, done
        
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        daddi $s3, $s3, 1           ; i++
        j     fib_loop

fib_loop1:
        dsub  $s7, $s3, $s0
        bgez   $s7, fib_done1    ; if i >= n, done
        
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        daddi $s3, $s3, 2           ; i++
        j     fib_loop1

fib_loop2:
        dsub  $s7, $s3, $s0
        beq   $s7, fib_done2    ; if i >= n, done
        
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        daddi $s3, $s3, 4           ; i++
        j     fib_loop2

fib_loop3:
        dsub  $s7, $s3, $s0
        beq   $s7, fib_done3    ; if i >= n, done
        
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        dadd  $s4, $s1, $s2         ; next = prev + curr
        dadd  $s1, $zero, $s2       ; prev = curr
        dadd  $s2, $zero, $s4       ; curr = next
        daddi $s3, $s3, 6          ; i++
        j     fib_loop3

fib_done1: 
        beq   $s7, $zero, fib_done
        dsub  $s1, $s2, $s1
        j     fib_done

fib_done2: 
        beq   $s7, $zero, fib_done
        dsub  $s4, $s2, $s1
        dadd  $s2, $zero, $s1
        dadd  $s1, $zero, $s4
        dsubi  $s3, $s3, 1
        beq   $s3, $s0, fib_done 
        dsub  $s4, $s2, $s1
        dadd  $s2, $zero, $s1
        dadd  $s1, $zero, $s4
        dsubi  $s3, $s3, 1
        beq   $s3, $s0, fib_done 
        dsub  $s4, $s2, $s1
        dadd  $s2, $zero, $s1
        dadd  $s1, $zero, $s4
        dsubi  $s3, $s3, 1
        beq   $s3, $s0, fib_done 
        j     fib_done

fib_done3: 
        beq   $s7, $zero, fib_done
        dsub  $s1, $s2, $s1
        j     fib_done

fib_done:
        ; Result in $s1 

        ; Print result message
        daddi $v0, $zero, 4
        daddi $a0, $zero, result_msg
        sd    $a0, 0($t8)
        sd    $v0, 0($t9)

        ; Print result
        daddi $v0, $zero, 2         ; 2 = print integer
        sd    $s1, 0($t8)
        sd    $v0, 0($t9)

        ; Print newline
        daddi $v0, $zero, 4
        daddi $a0, $zero, nl
        sd    $a0, 0($t8)
        sd    $v0, 0($t9)

        halt