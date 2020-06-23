package animal;

public class Mammifere extends Animal {
    public Mammifere(String name){super(name);}
    public Mammifere() {super();}

    public String getType()
    {
        String sentence;
        sentence = super.getType();
        sentence += " ";
        sentence += "Je suis un mammifère.";
        return sentence;
    }
}