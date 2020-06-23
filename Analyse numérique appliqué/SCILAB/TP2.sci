//Séance 2 : Exercice 3. Un système proie/prédateur
q=5 //numéro de la question traitée
//Initialiser
C0 = 25
R0 = 5
V0 = [C0;R0]
//la matrice de coefficients
A = [0.5 0.4;-0.104 1.1]
//nombre de mois
n = 20
//
//1ere méthode : utiliser une matrice M pour stoker les résultats
//
M = zeros(2,2)
//
M(1,1) = C0
//
M(2,1) = R0
//
//boucle pour calculer à chaque mois
//
for i = 2:n
//
M(1:2,i) = A*M(1:2,i-1)
//
end
//2e méthode : Dans une matrice V
V=V0
for i = 2:n
V(1:2,i) = A*V(1:2,i-1)
end
//Question 1 :
if q==1 then
//tracer
//1ere facon
scf(0)
clf(0)
//pour que l'origine s'affiche
a=get("current_axes");
a.x_location="origin";
a.y_location="origin";
xtitle("rats et chouettes en cours du temps","mois","effectif")
plot(V(1,:),'bp:')
plot(V(2,:),'gs-')
legend(['chouettes','rats (en milliers)'])
//
//2e façon
//
scf(1)
//
clf(1)
//
b=get("current_axes")
//
b.x_location="origin";
//
b.y_location="origin";
//
plot2d(1:n,V(1,:),color("red"))
//
plot2d(1:n,V(2,:),color("blue"))
end
//Question 2 :
if q==2 then
//on trace le nombre de chouettes par rapport à celui des rats
//au cours du temps.
//on saute les n premiers mois, on compte juqu'à m+n mois
//dans le but d'obtenir une droitem=10
M=[V(1,n);V(2,n)]
for i = 2:m
M(1:2,i) = A*M(1:2,i-1)
end
scf(0)
clf(0)
a=get("current_axes");
a.x_location="origin";
a.y_location="origin";
xtitle("chouettes en fonction de rats","rats(milliers)","chouettes ")
plot(M(2,:),M(1,:))
//
h=a.children(1).children(1);
//
h.thickness=2;
//
h.foreground=2;
//calculer la régression linéaire
[c,d,sig] = reglin(M(1,:),M(2,:));
disp("c = " + string(c)) //ratio chouettes/rats
end
//question 3
if q==3 then
//on a deviné que R_k = t%*R_(k-1) donc on trace R_k en fonction
//de R_(k-1)
m=10000
M=[V(1,n);V(2,n)]
for i = 2:m
M(1:2,i) = A*M(1:2,i-1)
end
scf(0)
clf(0)
//a=get("current_axes");
//a.x_location="origin";
//a.y_location="origin";
plot(M(2,1:m-1),M(2,2:m))
[t,d,sig] = reglin(M(2,1:m-1),M(2,2:m));
disp("t = " + string(t*100-100) +"%") //taux de croissance
end
//même chose pour les chouettes, à vous de terminer
//question 4
if q==4 then
//indication : si l'on a trouvé R_k = t*R_(k-1), alors R_k =
t^k*R_0
//donc, la représentation graphique de log(R_k) en fonction du
temps (k)
//devrait donner une droite de pente log(t)
//c'est la raison pour laquelle on trace log(R_k) en fonction du
temps
m=100
M=V0
for i = 2:m
M(1:2,i) = A*M(1:2,i-1)end
scf(0)
clf(0)
plot(0:m-1,log(M(2,:)))
[lt,d,sig] = reglin(0:m-1,log(M(2,:)));
disp("t = " + string(exp(lt))) //taux de croissance
end
//même chose pour les chouettes, à vous de terminer
//question 5
if q==5 then
m=100 //regarder ce que donne m =10 puis m = 100 puis m = 1000....
M=V0
for i = 2:m
M(1:2,i) = A*M(1:2,i-1)
end
scf(1)
clf(1)
//subplot(mnp) : divise la fenetre en m lignes et n colones et affiche
//le graphe sur la p ième sous-fenetre
subplot(221)
plot(0:m-1,log(M(2,:)))
xtitle("taux de croissance des rats","mois","log(rats)")
subplot(222)
plot(V(1,:),'bp:')
plot(V(2,:),'gs-')
xtitle("rats et chouettes en cours du temps","mois","effectif")
subplot(223)
xtitle("chouettes en fonction de rats","rats
(milliers)","chouettes")
plot(M(2,:),M(1,:))
subplot(224)
plot(M(2,1:m-1),M(2,2:m))
//pour tester le code pour différentes valeurs de C_0 et R_0
//il suffit de changer les valeur de C_0 et R_0 au départ
//à vous de réfléchir pour répondre aux autres parties de la
question 5
end
