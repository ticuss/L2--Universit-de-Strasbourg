.data
.globl buffer bufferFrase n offsetPA ANCHO ALTO PLANES COMPRESSION mensajeBMPn mensajeBMP
.globl NoBpp IMAGE_SIZE codigoASCII separador asterisco DIBHEADERzise mensajeBMPCompresion
.globl nRead caracter NombreArchivoOUTCpy nEscrMessage tamaBuff mensajeBMPTipoHeader numMaxCar
.globl pideFraseSecreta NoMaximoDeCaracteres EscribeOK SeHanEscrito Caracteres NoCarFrase
# on declare les variables globales pour qu'elles soient connues par tous les sous-routine
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
NoCarFrase: .word 0
mesNomreAchivoIN: .asciiz "Entrez le nom du fichier d'entrée\n"
messNom: .asciiz "\n Le nom de l'image BMP est: "
fpMessage: .asciiz "\n le descripteur de fichier est: "
nReadMessage: .asciiz "\nLe nombre d'octets lus est: "
nEscrMessage: .asciiz "\nEl Nombre d'octets Ecrits est: "
codigoASCII: .asciiz "\nLe code ASCII est"
caracter: .asciiz "\nle caracter est "
separador: .asciiz "\n"
asterisco: .asciiz "************\n"
NombreArchivoINCpy: .asciiz "/Users/g0sher/Desktop/bmpMIPSCod/perro.bmp"
NombreArchivoOUTCpy: .asciiz "/Users/g0sher/Desktop/bmpMIPSCod/perroc.bmp"
mensajeBMP:.asciiz "\nARCHIVE N'EST PAS BMP"
mensajeBMPn:.asciiz "\nLa taille du fichier est supérieure à 400 000 octets"
mensajeBMPTipoHeader:.asciiz "\nL'image ne fait pas 24 ou 32 pb SANS compression "
mensajeBMPCompresion:.asciiz "\nll´image ne doit pas être compressé"
mensajeBMP_no_existe_file:.asciiz "\nIl n'y a pas d´archive"
pideFraseSecreta: .asciiz  "\nEntrez une phrase secrète et terminez par le symbole &\n"
NoMaximoDeCaracteres: .asciiz "\nNombre maximum de caractères=" 
EscribeOK: .asciiz "\nLa phrase a été codée" 
SeHanEscrito:.asciiz "\nSe sont ecrit;"
Caracteres:.asciiz "  chars"
.text
.globl main
main:

#############################"  Lecture d´árchive BMP   ##############################################



 jal leeNombreArchivoBMPIN	#saute a la routine de saisie des noms des archives



li $v0,13	#ouvrir le fichier avec le nom donné à lire
#la $a0,NombreArchivoINCpy
la $a0,nombreIn	# En nombreIn il y a le debut du buffer du nom de l'image d'entree
li $a1,0	#ouvre à la lecture
li $a2,0	#il n'est pas utilisé
syscall
move $s0,$v0	#enregistre file descriptor en $s0 et en fp
sw $v0,fp	#enregistre file descriptor en  fp

beq $s0,-1, MENSAJEBMP_NO_EXITE_ARCHIVO	#si file descriptor =-1 ERROR de input. Saut au final....
##############################################################################################
# Remplir le buffer en mémoire avec le contenu du fichier
##############################################################################################"
li $v0,14	#lire le buffer du fichier
move $a0,$s0    #s0 a le file descriptor  
la $a1,buffer   #buffer est l'espace memoire ou notre fichier est stocke
li $a2,400000   #taille maximale d'octets à lire
syscall

move $s3,$v0	#enregistre la longueur lue en $s3 et en nRead
sw   $s3, nRead	#Enregistrer le numéro lu en nRead

li $v0,4	#montre NEWLINE
la $a0,separador
syscall

li $v0,4	#montre le mensage de nRead
la $a0,nReadMessage
syscall

li $v0,1	#montre nb.de bytes lue
move $a0,$s3	#En s3 est nb.de bytes lue
syscall

li $v0,16	#fermer le fichier avec le descripteur de lecture
move $a0,$s0
syscall

#############################################################################
#    Lire l'en-tête de l'archive dans le buffer
#############################################################################"


jal leeHeader	#saute à lire le header

#############################################################################
# Si la lecture de header est réussite, le travail continue
#############################################################################"

############################################################################
#   Lire la phrase secrete pour le codifier
############################################################################
jal  leeFrase 	#lee phrase à coder


###########################################################################
#  Codation
############################################################################"
jal codifica    #saute a la routine de codage

############################################################################
# garde l'image avec la codification
############################################################################
jal guardaImagen	#Garde l'image codifiee






j exit	#jusqu'a ici tout est normal, donc ca sort par la fonction exit
###########################################################################


###########################################################################
#condition d'erreur:
##########################################################################
MENSAJEBMP_NO_EXITE_ARCHIVO:
li $v0,4
la $a0,mensajeBMP_no_existe_file	#envoi erreur que l archive n existe pas
syscall
j exit



exit:
li $v0,10
syscall
