.data

.text

.globl  guardaImagen	#definida como global y visible desde otras subrutinas
guardaImagen:	#nombre de subrutina



addi    $sp, $sp, -4	#guarda registros externos para no contaminarlos con calculos de rutina
sw      $ra, 0($sp)
addi    $sp, $sp, -4
sw 	$a3, 0($sp)
addi    $sp, $sp, -4
sw 	$a2, 0($sp)
addi    $sp, $sp, -4
sw 	$a1, 0($sp)
addi    $sp, $sp, -4
sw      $a0, 0($sp)
addi    $sp, $sp, -4
sw      $s0, 0($sp)
addi    $sp, $sp, -4
sw      $s1, 0($sp)
addi    $sp, $sp, -4
sw      $s2, 0($sp)
addi    $sp, $sp, -4
sw      $s3, 0($sp)
addi    $sp, $sp, -4
sw      $s4, 0($sp)
addi    $sp, $sp, -4
sw      $s5, 0($sp)
addi    $sp, $sp, -4
sw      $s6, 0($sp)
addi    $sp, $sp, -4
sw      $s7, 0($sp)



li $v0,13	#abre file con el nombre dado para escribir
#la $a0,NombreArchivoOUTCpy
la $a0,nombreOut
li $a1,1
li $a2,0
syscall
move $s0,$v0	#guarda file descriptor en $s0 y en gp
lw   $s3, nRead	#carga no de  bytes de buffer guardados en  en nRead
li $v0,15	# carga buffer en archivo
move $a0,$s0    #usa file descriptor en $s0
li $t1 ,0
la  $a1,buffer	#buffer a escribir
move $a2,$s3	#no de bytes a escribir
syscall

move $t6,$v0	#guarda bytes escritos en $t1

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

li $v0,4	#muestra mensaje de nRead
la $a0,nEscrMessage
syscall

li $v0,1	#muestra en pantalla No. escrito
move $a0,$t6
syscall

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall


li $v0,4	#muestra frase
la $a0,EscribeOK
syscall


li $v0,16	#cierra file con descriptor de lectura
move $a0,$s0
syscall




lw      $s7, 0($sp)	#devuelve registros externos con valores antes de la llamada
addi    $sp, $sp, 4  
lw      $s6, 0($sp)
addi    $sp, $sp, 4  
lw      $s5, 0($sp)
addi    $sp, $sp, 4 
lw      $s4, 0($sp)
addi    $sp, $sp, 4  
lw      $s3, 0($sp)
addi    $sp, $sp, 4  
lw      $s2, 0($sp)
addi    $sp, $sp, 4  
lw      $s1, 0($sp)
addi    $sp, $sp, 4  
lw      $s0, 0($sp)
addi    $sp, $sp, 4  
lw      $a0, 0($sp)
addi    $sp, $sp, 4
lw      $a1, 0($sp)
addi    $sp, $sp, 4
lw      $a2, 0($sp)
addi    $sp, $sp, 4
lw      $a3, 0($sp)
addi    $sp, $sp, 4
lw      $ra, 0($sp)
addi    $sp, $sp, 4



    # sale de subrutina
jr      $ra
