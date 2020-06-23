.data
.text
.globl  leeHeader 	#declara leeHeader para que sea llamado desde afuera
leeHeader:	#nombre de rutina

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





####### 1 caracter de buffer ###################################"
lb $t1,buffer	#carga 1er byte de buffer

move $s1,$t1	#carga en $s1 primer caracter
####### 2 caracter de buffer ####################################
lbu $t1,buffer+1	#carga 2o byte de imagen

move $s2,$t1	#carga en $s1 2o caracter

bne $s1,0x42, MENSAJE	#salta a MENSAJE si archivo NO es BMP
bne $s2,0x4D, MENSAJE	#salta a MENSAJE si archivo NO es BMP

####### 3 ,4,5,6 caracter de buffer forman n : largo del archivo #########################
lbu $t1,buffer+2	#carga  bytes de buffer de imagen
lbu $t2,buffer+3	#carga  bytes de buffer de imagen
lbu $t3,buffer+4	#carga  bytes de buffer de imagen
lbu $t4,buffer+5	#carga  bytes de buffer de imagen

######## t4x256###################

mulu  $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t2x256###################

mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2+t3+t4 #######################""

addu $t1,$t1,$t2	#t1=t1+t2
addu $t1,$t1,$t3	#t1=t1+t2+t3
addu $t1,$t1,$t4	#t1=t1+t2+t3+t4
move $s1,$t1		#guarda resultado en $s1

sw $s1,n	#guarda en n  Largo del archivo

lw $t1,tamaBuff	
bgeu  $s1,$t1, MENSAJEn	#sale si archivo BMP es mayor que buffer

####### Lee 4 bytes inutiles #########################
lbu $t1,buffer+6	#carga  bytes de buffer de imagen
lbu $t2,buffer+7	#carga  bytes de buffer de imagen
lbu $t3,buffer+8	#carga  bytes de buffer de imagen
lbu $t4,buffer+9	#carga  bytes de buffer de imagen


###########"Lee 4 bytes para Offset de Pixmap
lb $t1,buffer+10	#carga  bytes de buffer de imagen
lb $t2,buffer+11	#carga  bytes de buffer de imagen
lb $t3,buffer+12	#carga  bytes de buffer de imagen
lb $t4,buffer+13	#carga  bytes de buffer de imagen

######## t4x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t2x256###################

mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2+t3+t4 #######################""

addu $t1,$t1,$t2	#t1=t1+t2
addu $t1,$t1,$t3	#t1=t1+t2+t3
addu $t1,$t1,$t4	#t1=t1+t2+t3+t4
move $s1,$t1		#guarda resultado en $s1

sw $s1,offsetPA	#guarda en offsetBM  del archivo

###########"Lee 4 bytes para DIBHEADERsize
lb $t1,buffer+14	#carga  bytes de buffer de imagen
lb $t2,buffer+15	#carga  bytes de buffer de imagen
lb $t3,buffer+16	#carga  bytes de buffer de imagen
lb $t4,buffer+17	#carga  bytes de buffer de imagen

######## t4x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t2x256###################

mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2+t3+t4 #######################""

addu $t1,$t1,$t2	#t1=t1+t2
addu $t1,$t1,$t3	#t1=t1+t2+t3
addu $t1,$t1,$t4	#t1=t1+t2+t3+t4
move $s1,$t1		#guarda resultado en $s1

sw $s1,DIBHEADERzise	#guarda en  DIBHEADERzise tamano de DIBHEADERzise

beq $s1,0x6c ,DETALLES_IMAGEN #Revisa el tipo de header
beq $s1,0x7c ,DETALLES_IMAGEN #Revisa el tipo de header
j MENSAJETipoHeader #SI BMP no es de tipo: 0x6c o 0x7c sale

DETALLES_IMAGEN:
###########"Lee 4 bytes para ANCHO
lb $t1,buffer+18	#carga  bytes de buffer de imagen
lb $t2,buffer+19	#carga  bytes de buffer de imagen
lb $t3,buffer+20	#carga  bytes de buffer de imagen
lb $t4,buffer+21	#carga  bytes de buffer de imagen

######## t4x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t2x256###################

mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2+t3+t4 #######################""

addu $t1,$t1,$t2	#t1=t1+t2
addu $t1,$t1,$t3	#t1=t1+t2+t3
addu $t1,$t1,$t4	#t1=t1+t2+t3+t4
move $s1,$t1		#guarda resultado en $s1

sw $s1,ANCHO	#guarda ANCHO 

###########"Lee 4 bytes para ALTO
lbu  $t1,buffer+22	#carga  bytes de buffer de imagen
lbu $t2,buffer+23	#carga  bytes de buffer de imagen
lbu $t3,buffer+24	#carga  bytes de buffer de imagen
lbu $t4,buffer+25	#carga  bytes de buffer de imagen

######## t4x256###################

#sw $t1,ESPACIO

mulu   $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
mflo  $t4

######## t4x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t2x256###################

mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2+t3+t4 #######################""

addu $t1,$t1,$t2	#t1=t1+t2
addu $t1,$t1,$t3	#t1=t1+t2+t3
addu $t1,$t1,$t4	#t1=t1+t2+t3+t4
move $s1,$t1		#guarda resultado en $s1

sw $s1,ALTO	#guarda ALTO

###########"Lee 2 bytes para Planes
lbu  $t1,buffer+26	#carga  bytes de buffer de imagen
lbu $t2,buffer+27	#carga  bytes de buffer de imagen

######## t2x256###################


mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2 #######################""

addu $t1,$t1,$t2	#t1=t1+t2

move $s1,$t1		#guarda resultado en $s1

sw $s1,PLANES	#guarda PLANES

###########"Lee 2 bytes para NoBpp
lbu  $t1,buffer+28	#carga  bytes de buffer de imagen
lbu $t2,buffer+29	#carga  bytes de buffer de imagen

######## t2x256###################


mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2 #######################""

addu $t1,$t1,$t2	#t1=t1+t2

move $s1,$t1		#guarda resultado en $s1

sw $s1,NoBpp	#guarda  NoBpp 

###########"Lee 4 bytes para COMPRESSION
lbu  $t1,buffer+30	#carga  bytes de buffer de imagen
lbu $t2,buffer+ 31	#carga  bytes de buffer de imagen
lbu $t3,buffer+ 32	#carga  bytes de buffer de imagen
lbu $t4,buffer+ 33	#carga  bytes de buffer de imagen

######## t4x256###################


mulu   $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
mflo  $t4


######## t4x256x256###################


mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo


######## t3x256###################


mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t3x256x256###################

mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t2x256###################


mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2+t3+t4 #######################""

addu $t1,$t1,$t2	#t1=t1+t2
addu $t1,$t1,$t3	#t1=t1+t2+t3
addu $t1,$t1,$t4	#t1=t1+t2+t3+t4
move $s1,$t1		#guarda resultado en $s1


sw $s1,COMPRESSION	#guarda  COMPRESION 

bne $s1,0,MENSAJECompresion #sale si hay compresion


###########"Lee 4 bytes para Tanano de Imagen
lbu  $t1,buffer+34	#carga  bytes de buffer de imagen
lbu $t2,buffer+ 35	#carga  bytes de buffer de imagen
lbu $t3,buffer+ 36	#carga  bytes de buffer de imagen
lbu $t4,buffer+ 37	#carga  bytes de buffer de imagen

######## t4x256###################


mulu   $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
mflo  $t4

######## t4x256x256###################


mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

######## t4x256x256x256###################

mulu $t4,$t4,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo


######## t3x256###################


mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo



######## t3x256x256###################



mulu $t3,$t3,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo



######## t2x256###################


mulu $t2,$t2,256	#en $t4 y LO queda low order 32 bits y en HIGH high order de $t4x256
mfhi $s1 	#en $s1 estan los 32 bits superiores de la multiplicacion  	
#mflo

#########  t1+t2+t3+t4 #######################""

addu $t1,$t1,$t2	#t1=t1+t2
addu $t1,$t1,$t3	#t1=t1+t2+t3
addu $t1,$t1,$t4	#t1=t1+t2+t3+t4
move $s1,$t1		#guarda resultado en $s1


sw $s1,IMAGE_SIZE	#guarda Tamano de imagen


j salidaNormal	#caso en que no hay error



#condiciones de error:


MENSAJEn:
li $v0,4
la $a0,mensajeBMPn		# la imagen no cabe en buffer
syscall
j exit

MENSAJETipoHeader:
li $v0,4
la $a0,mensajeBMPTipoHeader	# El tipo de imagen es inadecuado para codificar
syscall
j exit

MENSAJECompresion:
li $v0,4
la $a0,mensajeBMPCompresion	# La imagen esta comprimida , No sirve
syscall
j exit

MENSAJE:

li $v0,4
la $a0,mensajeBMP		#La imagen nNO es BMP
syscall



exit:				#Sale del proceso si la Imagen NO es adecuada 
li $v0,10
syscall






salidaNormal:		#Continua el proceso

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


