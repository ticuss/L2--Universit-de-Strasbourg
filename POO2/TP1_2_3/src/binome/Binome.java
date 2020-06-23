package binome;

public class Binome {
   
	protected double a, b, c, dis;

	 public static int main(String arg[]) {
	        Binome b[] = new Binome[3];
	        int i, k;
	        b[0] = Binome.creation(1.0, 0.0, 1.0);
	        b[1] = Binome.creation(1.0, 2.0, 1.0);
	        b[2] = Binome.creation(1.0, 1.0, 1.0);
	        for (i = 0; i < 3; i++) {
	            System.out.print("" + i + ": ");
	            b[i].racine();
	            if (b[i].nb_racine() == 0) {
	                System.out.println("Pas de solution!");
	            } else {
	                for (k = 1; k <= b[i].nb_racine(); k++) {
	                    System.out.println("" + b[i].valeur_racine(k) + " ");
	                }
	            }
	        }
	        return 0;
	    }

    public static Binome creation(double pa, double pb, double pc) {
        double delta;
        delta = pb * pb - 4.0 * pa * pc;
        if (delta < 0.0) {
            return new BinomeSol0(pa, pb, pc, delta);
        } else if (delta == 0.0) {
            return new BinomeSol1(pa, pb, pc, delta);
        } else {
            return new BinomeSol2(pa, pb, pc, delta);
        }
    }

    public void racine()
    {
        System.out.println("Erreur si ici !");
    }

    public int nb_racine()
    {
        System.out.println("Erreur si ici !");
        return 0;
    }

    public double valeur_racine(int i)
    {
        System.out.println("Erreur si ici !");
        return 0.0;
    }

   
}