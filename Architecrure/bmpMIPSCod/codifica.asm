.data 	#segment de données

DELTA:.word 3           # Numero des octets par pixel DELTA= 3 ou 4 si 24 ou 32   bits pp
ANCHOTOTAL: .word 0    #largeur total en octets de buffer , y compris padding
ANCHOIMAGEN:.word 0     #largeur de l'image en octets de buffer
TAMTOTAL:.word 0	#taille total de l'image
carAmper:.word 0	#caracter dans leauel on codifie &
encontreAmpersand:.asciiz "Trouve & en caracter: "
.text
.globl codifica

codifica:

addi    $sp, $sp, -4	#tenir des registres externes afin de ne pas les contaminer avec des calculs de routine
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











############################################################################""
#Calcul de padding
############################################################################
#
# LARGEURTOTAL=  (ANCHO*DELTA*8+31)/32 arrondi inferior x 4
#
############################################################################
lw $t1,NoBpp		#t1=No de bits pp
divu $t1,$t1,8          #t1=NoBpp/8
sw $t1,DELTA		#DELTA=NoBpp/8 . enregistre en DELTA


lw $t1,ANCHO		#t1=ANCHO
lw $t2,DELTA		#t2=DELTA
mulu  $t2,$t2,$t1	#t2=DELTAxANCHO
mulu  $t2,$t2,8		#t2=DELTAxANCHOx8
addiu $t2,$t2,31	#t2=DELTAxANCHOx8+31
divu $t2,$t2,32		#t2=(DELTAxANCHOx8+31)/32
mulu $t2,$t2,4		#t2=[(DELTAxANCHOx8+31)/32]x4
sw $t2,ANCHOTOTAL	#LARGEURTOTAL=[(DELTAxANCHOx8+31)/32]x4


############################################################################""
#Calcul de LARGEUR DE L'IMAGE
############################################################################
#
# ANCHOIMAGEN=  (ANCHO*DELTA)
#
############################################################################


lw $t1,ANCHO		#t1=ANCHO
lw $t2,DELTA		#t2=DELTA
mulu  $t2,$t2,$t1	#t2=DELTAxANCHO
sw $t2,ANCHOIMAGEN	#ANCHOIMAGEN=DELTAxANCHO


############################################################################""
#Calcul de TAILLE TOTAL
############################################################################
#
# TAMTOTAL=  ALTO* ANCHOTOTAL
#
############################################################################
lw $t1,ANCHOTOTAL		#t1=ANCHOTOTAL
lw $t2,ALTO			#t2=ALTO
mulu  $t2,$t2,$t1		#t2=ALTOxANCHOTOTAL
sw $t2,TAMTOTAL			#TAMTOTAL=ALTOxANCHOTOTAL



############################################################################
# Boucle de buffer
############################################################################
#Selection des registres:
#s0=xbit                identite de bit dans le charactere de gauche a droite: 0->7 = ibit % 8
#s1=idchar              Indice de caractère dans la phrase           =ibit/8  
#s3=idRGB		Indice de octet RGBA pour chaque pixel: 1,2,3,4    voir ci-dessous
#s4=ux			Position de octet de l'imagen dans chaque ligne:0->ANCHOTOTAL voir ci-dessous
#s5=x   		Masque de xbit  a un 1 en position de xbit
#t0=ibyte		Indice d'octet dans buffer de l'image
#t1=ibit		Indice de bits qui ramasse toutes les characters de la frase
#t2=pivot               apporter des constantes dans les calculs
#t3=pivot               ''  ''   ''    ''   ''        ''     ''




lw $t0,offsetPA			 #Initialisation t0=OFFSET <==> ibyte=offsetPA
li $t1,0       			 #t1=0  Initialisation du compteur de bits  (ibit=0)    
li $s5,0x80    			 #Initialisation masque de xbit x=10000000

do_1:				#boucle de passage de buffer


li $t2,8			#enregistre 8 en pivot t2
divu   $t1,$t2			#divize ibit/8 et on obtien idchar et aussi xbit = ibit % 8
mfhi $s0			#xbit=s0
mflo $s1			#idchar=s1

do_2:				#boucle de revision de ibyte pour accepter ou non
lw $t3,offsetPA        		#charge offsetPA en pivot t3
subu $t2,$t0,$t3		#t2 = ibyte - offset; t2=position real d'octet de l'image

lw $t3,ANCHOTOTAL 		#chqrge ANCHOTOTAL en pivot t3
divu $t2,$t3			#divise position real d'octet en l'image/ANCHOTOTAL
				# on obtien position en ligne ux comme le reste
mfhi $s4			#ux=s4 ; ux= (r-offset)%(ANCHOTOTAL) ; ibyte=r


lw $t3,DELTA 			#chqrge DELTA en pivot t3
divu $s4,$t3            	#on obtien  ux%DELTA en HI de division
mfhi $s3               		#ux%DELTA; 
addiu $s3,$s3,1			#idRGB= ux%DELTA+1= 1,2,3 (24bpp)  o  1, 2, 3, 4(32bbp)
				#s3=idRGB    1=R ,2=G ,3=B ,4=Alfa			
			
beq $s3,4,NO_ACEPTADO 		#si idRGB = 4 saute et n'accepte pas 
idRGB_123:			# Si on est ici c'est parceaue idRGB != 4	
lw $t3,ANCHOIMAGEN 		#charge ANCHOIMAGEN en pivot t3
blt $s4,$t3,ACEPTADO		#si ux<ANCHOIMAGEN et idRGB !=4 le ibyte 
				#est accepter==> saut a ACEPTADO

NO_ACEPTADO:			#l'octet:ibyte  N'est pas accepte
addiu $t0,$t0,1			#augmente ibyte en 1, ibyte=ibyte+1
while_2: b  do_2		#saut inconditionelle a do_2
				#jusqu'a ca soit accepter

ACEPTADO:			 #ibyte est accepte	
				#continuer à coder
lbu $t3,buffer($t0) 	        #enregistre en pivot t3 l'octet de l'image: buffer[ibyte]	
lbu $t2,bufferFrase($s1)	#enregistre en pivot t2 : bufferFrase[idchar]	

and   $t2,$t2,$s5		#enregistre en pivot t2 le resultat de  (mask de xbit(s5=x) AND frase[idchar])
beqz $t2, ES_0 			#saut a ES_0 si le bit dans bufferFrase[idchar]  pos. xbit est 0

ES_1:				#bit de charactere bufferFrase[idchar] dans position: xbit est 1
ori $t3,$t3,0x01                #bit 0 de  bufferFrase[ibyte] est  avec masque: 00000001
b  CONTINUE			#saut pour CONTINUE

ES_0:				#bit de charactere bufferFrase[idchar] dans position: xbit est 0
andi $t3,$t3,0xFE		#bit 0 de  buffer[ibyte] est mis a 0
				#avec masque: 11111110
CONTINUE:
sb  $t3,buffer($t0) 		#enregistre dans la memoire l'octet de l'image recement codifie
			  	
bne  $s0,7 NO_FIN_CHAR		#saut si xbit!=7
FIN_CHAR:			#xbit=7	termine de codifier le charactere	
li $s5,0x80    			 #inisialisation masque de xbit x=10000000
lbu $t3,bufferFrase($s1)	 #charge en pivot t3 frase[idchar]	
beq $t3,0x26, TERMINO		# Quitter si le caractère encodé est '&' cod. ascii 0x26
j noAmpersand			#saut a noAmpersand



NO_FIN_CHAR:	 		#continue a codifier
srl $s5,$s5,1			#lance le masque xbit vers la droite 1 bit

noAmpersand:
addiu $t0,$t0,1			#t0=t0+1 <==> ibyte=ibyte+1
addiu $t1,$t1,1			#t1=t1+1 <==> ibit=ibit+1
lw $t2,offsetPA			#charge dans pivot t2 offsetPA
subu $t2,$t0,$t2		#t2=ibyte-OFFSET
lw $t3,TAMTOTAL                 #charge dans pivot t3 TAMTOTAL 
while_1:bltu $t2,$t3,do_1	#boucle a do_1 si (ibyte-offsetPA) < TAMTOTAL

TERMINO:
sw $s1,carAmper			#enregistre dans carAmper le charactere ou il a trouve &


li $v0,4	#exemple de phrase
la $a0,encontreAmpersand
syscall

li $v0, 1	#ecrire no.caracteres quand il trouve &
move $a0,$s1
syscall

li $v0,4	#exeple NEWLINE
la $a0,separador
syscall



# À ce stade, il a été trouvé & 






lw      $s7, 0($sp)	#renvoie des enregistrements externes avec des valeurs avant l'appel
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


jr $ra	#ça sort de la routine
