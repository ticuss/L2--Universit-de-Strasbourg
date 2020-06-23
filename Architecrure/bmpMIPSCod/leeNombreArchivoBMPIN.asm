.data 
nombreIn: .space 40
nombreOut: .space 40
pideNombreArchivoIN: .asciiz "\nEntre nombre de archivo a codificar (< 40 caracteres)"
pideNombreArchivoOUT: .asciiz "\nEntre nombre de archivo que recibira codificacion,\npuede ser el mismo(< 40 caracteres)"
.text

.globl  leeNombreArchivoBMPIN nombreIn nombreOut	#define como globales para ser conocidos afuera
 
 leeNombreArchivoBMPIN:	#nombre de subrutina

addi    $sp, $sp, -4	#guarda en STACK registros externos para no contaminarlos con calculos de rutina
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



li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

li $v0,4	#muestra frase
la $a0,pideNombreArchivoIN
syscall

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

li $v0,8	#lee nombre de archivo desde consola
la $a0, nombreIn
li $a1,40
syscall

###################################################################################"
#Elimina \n del final del nombreIn 
###################################################################################
li $t1,39	#guarda indice de loop
la  $s1,nombreIn+39	#guarda direccion de byte final de nombreIn
do1:
lbu  $s2,($s1)	#guarda contenido de s1 en s2
bne   $s2,0x00, NEWL	#revisa si es NEWLINE y salta
subi   $s1,$s1,1	#decrementa direccion
subiu  $t1,$t1,1	#decrementa indice
while1:bgez  $t1 do1
j NEXT
NEWL:
li $s3,0	#colca un 0 en lugar de newline
sb $s3,($s1)
NEXT:

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

li $v0,4	#muestra frase
la $a0,pideNombreArchivoOUT	#pide nombre de archivo donde se guardara la frase secreta
syscall				#SE crea el archivo con el nombre dado

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

li $v0,8	#lee nombre de archivo de consola
la $a0, nombreOut
li $a1,40
syscall

###################################################################
# Saca \n del final del nombre leido
################################################################"
li $t1,39	#guarda indice de loop
la  $s1,nombreOut+39	#guarda direccion de byte final de nombreIn
do2:
lbu  $s2,($s1)	#guarda contenido de si en s2
bne   $s2,0x00, NEWL1	#revisa si es NEWLINE y salta
subi   $s1,$s1,1	#decrementa direccion
subiu  $t1,$t1,1	#decrementa indice
while2:bgez  $t1 do2
j NEXT1
NEWL1:
li $s3,0	#colca un 0 en lugar de newline : \n
sb $s3,($s1)	#guarda el 0 en la posicion del donde estaba \n
NEXT1:
#Sale , Los nombres son variables globales leibles desde afuera

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
    # return from function
jr      $ra
