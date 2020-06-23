package animal;

public class Homme extends Mammifere {
    public Homme(String name){super(name);}
    public Homme() {super();}

    public String getType()
    {
        String sentence;
        sentence = super.getType();
        sentence += " ";
        sentence += "Je suis un homme.";
        return sentence;
    }
}