package animal;

public class Poisson extends Animal {
    
	public Poisson(String name)
    {
    	super(name);
    }
    public Poisson() 
    {
    	super();
    }

    public String getType()
    {
        String sentence;
        sentence = super.getType();
        sentence += " ";
        sentence += "Je suis un poisson.";
        return sentence;
    }
}