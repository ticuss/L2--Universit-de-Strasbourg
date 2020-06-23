package binome;

public class BinomeSol1 extends Binome {
    // Donnees:
    protected double a, b, c, dis, racine;

    // Methodes
    public BinomeSol1(double pa, double pb, double pc, double pdis) {
        a = pa;
        b = pb;
        c = pc;
        dis = pdis;
    }

    public void racine()
    {
        racine=-b/(2*a);
        return;
    }

    public int nb_racine()
    {
        return 1;
    }

    public double valeur_racine(int i)
    {
        return racine;
    }
}