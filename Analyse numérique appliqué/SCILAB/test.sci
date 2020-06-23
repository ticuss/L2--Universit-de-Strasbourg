
//Initialiser
C0 = 25
R0 = 5
V0 = [C0;R0]
//la matrice de coefficients
A = [0.5 0.4;-0.104 1.1]
//nombre de mois
n = 20
M = zeros(2,2)
M(1,1) = C0
M(2,1) = R0
V=V0
for i = 2:n
V(1:2,i) = A*V(1:2,i-1)


scf(0)
clf(0)

a=get("current_axes");

a.x_location="origin";
a.y_location="origin";
xtitle("rats et chouettes en cours du temps","mois","effectif")
plot(V(1,:),'bp:')
plot(V(2,:),'gs-')
legend(['chouettes','rats (en milliers)'])

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
