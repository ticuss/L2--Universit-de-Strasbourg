.data
.globl buffer bufferFrase n offsetPA ANCHO ALTO PLANES COMPRESSION mensajeBMPn mensajeBMP
.globl NoBpp IMAGE_SIZE codigoASCII separador asterisco DIBHEADERzise mensajeBMPCompresion
.globl nRead caracter NombreArchivoOUTCpy nEscrMessage tamaBuff mensajeBMPTipoHeader numMaxCar
.globl pideFraseSecreta NoMaximoDeCaracteres EscribeOK
buffer: .space 400000
bufferFrase: .space 400
NombreArchivoIN: .space 100
NombreArchivoINBuffer: .space 100
bufferBytesInd: .space 8
nRead: .space 4
n: .space 4  
offsetPA: .space 4  
DIBHEADERzise: .space 4
ANCHO: .space 4
ALTO: .space 4
PLANES: .space 4
NoBpp: .space 4
COMPRESSION: .space 4
IMAGE_SIZE: .space 4
ESPACIO: .space 4
fp: .space 4
gp: .space 4
tamaBuff: .word 400000
numMaxCar: .word 0
mesNomreAchivoIN: .asciiz "Entre nombre de archivo de entrada\n"
messNom: .asciiz "El nombre de la Imagen BMP es: "
fpMessage: .asciiz "El file descriptor es: "
nReadMessage: .asciiz "El No de bytes leido es: "
nEscrMessage: .asciiz "El No de bytes Escritos es: "
codigoASCII: .asciiz "El codigo ASCII es "
caracter: .asciiz "El caracter es "
separador: .asciiz "\n"
asterisco: .asciiz "************\n"
NombreArchivoINCpy: .asciiz "/home/ivan/HOMEwin/tareas2018/federico/MIPS/tests/test4a/perro.bmp"
NombreArchivoOUTCpy: .asciiz "/home/ivan/HOMEwin/tareas2018/federico/MIPS/tests/test4a/perroC.bmp"
mensajeBMP:.asciiz "ARCHIVO NO ES BMP"
mensajeBMPn:.asciiz "Tamano de ARCHIVO es mayor que 400000 bytes"
mensajeBMPTipoHeader:.asciiz "Imagen No es de 24 o 32 bbp SIN compresion (Windows NT y superior)"
mensajeBMPCompresion:.asciiz "Imagen No debe estar comprimida"
mensajeBMP_no_existe_file:.asciiz "No existe archivo"
pideFraseSecreta: .asciiz  "Entre frase secreta y termine con el simbolo &\n"
NoMaximoDeCaracteres: .ascii "Numero maximo de caracteres=" 
EscribeOK: .ascii "La frase ha sido codificada" 

.text
#.globl main
main:

#############################"  Lectura de Imagen desde archivo ##############################################

li $v0,4	#muestra mensaje de reconocimiento
la $a0,messNom
syscall

 jal leeNombreArchivoBMPIN

li $v0,13	#abre file con el nombre dado para leer
#la $a0,NombreArchivoINCpy
la $a0,nombreIn
li $a1,0
li $a2,0
syscall
move $s0,$v0	#guarda file descriptor en $s0 y en fp

sw $v0,fp	#guarda file descriptor en  fp

beq $s0,-1, MENSAJEBMP_NO_EXITE_ARCHIVO

#1.Lee buffer a memoria dese archivo

li $v0,14	#lee buffer desde archivo
move $a0,$s0
la $a1,buffer
li $a2,400000
syscall

move $s3,$v0	#guarda el largo leido en $s3 y en nRead
sw   $s3, nRead	#Guarda numero leido en nRead

li $v0,4	#muestra NEWLINE
la $a0,separador
syscall

li $v0,4	#muestra mensaje de nRead
la $a0,nReadMessage
syscall

li $v0,1	#muestra No.de bytes leidos 
move $a0,$s3
syscall

li $v0,16	#cierra file con descriptor de lectura
move $a0,$s0
syscall

##################################TRABAJO CON ARCHIVO ########################################"

####### 1 caracter de buffer ###################################"
lb $t1,buffer	#carga 1er byte de imagen

move $s1,$t1	#carga en $s1 primer caracter
####### 2 caracter de buffer ####################################
lbu $t1,buffer+1	#carga 2o byte de imagen

move $s2,$t1	#carga en $s1 2o caracter

bne $s1,0x42, MENSAJE	#sale si archivo NO es BMP
bne $s2,0x4D, MENSAJE	#sale si archivo NO es BMP

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
j MENSAJETipoHeader

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

bne $s1,0,MENSAJECompresion #salta si hay compresion


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


#################################### NO SE LEE MAS INFOHEADER ################################################
############# SE USA OFFSET PARA LOCALIZAR COMIENZO DE PIXMAP ################################################


jal  leeFrase 	#lee frase a codificar





jal guardaImagen	#Guarda imagen codificada


#########################################Guarda buffer en Archivo de Salida###################################"



j exit
################################################################################################################"
MENSAJEBMP_NO_EXITE_ARCHIVO:
li $v0,4
la $a0,mensajeBMP_no_existe_file
syscall
j exit





MENSAJEn:
li $v0,4
la $a0,mensajeBMPn
syscall
j exit

MENSAJETipoHeader:
li $v0,4
la $a0,mensajeBMPTipoHeader
syscall
j exit
MENSAJECompresion:
li $v0,4
la $a0,mensajeBMPCompresion
syscall
j exit



MENSAJE:

li $v0,4
la $a0,mensajeBMP
syscall



exit:
li $v0,10
syscall
