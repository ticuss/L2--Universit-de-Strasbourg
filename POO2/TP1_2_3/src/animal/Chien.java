package animal;

public class Chien extends Mammifere {
    public Chien(String name){super(name);}
    public Chien() {super();}

    public String getType()
    {
        String sentence;
        sentence = super.getType();
        sentence += " ";
        sentence += "Je suis un chien.";
        return sentence;
    }
}