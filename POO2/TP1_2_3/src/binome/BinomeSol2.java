package binome;

public class BinomeSol2 extends Binome {
    protected double a, b, c, dis, racine1, racine2;

    public BinomeSol2(double pa, double pb, double pc, double pdis) {
        a = pa;
        b = pb;
        c = pc;
        dis = pdis;
    }

    public void racine()
    {
        racine1=(-b-Math.sqrt(dis))/(2*a);
        racine2=(-b+Math.sqrt(dis))/(2*a);
        return;
    }

    public int nb_racine()
    {
        return 2;
    }

    public double valeur_racine(int i)
    {
        return i==1 ? racine1 : racine2;
    }
}