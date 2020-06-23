.data


.text

.globl  leeFrase 
leeFrase:



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


####################################################################
# Calculo de numero maximo de caracteres a introducir
#  NUM_MAX_CAR=ALTOxANCHOx3/8
####################################################################
lw $s3,ANCHO	#carga ALTO y ANCHO
lw $s4,ALTO
mul  $s3  $s3,$s4
mfhi $t1 	#word mas significativa de multiplicacion de ALTOxANCHO
		# solo sirve si las cantidades son muy grandes
mflo $t0	#s3 y t0 =word menos significativa de multiplicacion de ALTOxANCHO
mulu $s3,$s3,3  #s3=ANCHOxALTOx3
divu  $s3,$s3,8  #t0=ANCHOxALTOx8/8  , entero
sw $s3,numMaxCar#guarda en memoria numMaximo de caracteres
move $s7,$s3	#en s7 esta el maximo de caracteres

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

li $v0,4	#muestra frase
la $a0,pideFraseSecreta
syscall

li $v0,4	#muestra frase
la $a0,NoMaximoDeCaracteres
syscall

li $v0,1	#muestra No. maximo de caracteres a escribir
move $a0,$s7
syscall

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall


li $s0,0x21		#coloca en posicion 0 de frase el simbolo !
li $t0,0		#0x21= codigo ascci de '!' 
sb $s0,bufferFrase($t0) #coloca ! en posicion 0 de bufferFrase


li $s0,0x26		#0x26= codigo ascci de '&' 
move $t0,$s7,		#t0=numMaxCar
sb $s0,bufferFrase($t0) #coloca & en posicion no maximo de caracteres de bufferFrase como precaucion


li $t0,1		#coloca contador de caracteres en 1

do:
li $v0,12  		# lee caracter desde consola
syscall
sb $v0,bufferFrase($t0)	#guarda caracter en bufferFrase[t0]
beq $v0,0x26,TERMINADOR	#sale si caracter = &    (0x26= cod. ascci de '&')
addiu  $t0,$t0,1	#incrementa contador
while: ble  $t0,$s7,do	#retorna a do si se esta dentro de largo de Maximo de caracters
TERMINADOR:
li $t1,0		#agrega 0 despues de & en frase para asegurarse un
addiu  $t0,$t0,1	#buen despliegue con print
sb $t1,bufferFrase($t0)

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

li $v0,4	#muestra frase
la $a0,SeHanEscrito
syscall

addi $t0,$t0,-1	#corrige el contador de caracteres para no contar 0 al final

move $a0,$t0	#escribe el numero de caracteres entrado
li $v0,1
syscall

sw $t0,NoCarFrase #guarda en memoria el numero de caracteres entrados


li $v0,4	#muestra frase
la $a0,Caracteres
syscall


li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

lw      $s7, 0($sp)	#devuelve registros externos con los valores antes de la llamada
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
