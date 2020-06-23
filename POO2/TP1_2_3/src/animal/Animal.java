package animal;

public class Animal {
    private String name;

    public Animal(String name)
    {
        this.name=name;
    }
    public Animal(){};

    public String getType()
    {
        String prop;
        prop = "Je suis un animal";
        if(name!=null && !name.isEmpty())
        	prop += " de nom "+name;
        prop+=".";
        return prop;
    }
    
    public static void main(String[] args) {
        Animal[] animaux = new Animal[5];
        animaux[0] = new Animal("Truc");
        animaux[1] = new Animal();
        animaux[2] = new Chien("Medor");
        animaux[3] = new Poisson();
        animaux[4] = new Homme("Laurent");

        for (int i = 0; i < animaux.length; i++)
            System.out.println(animaux[i].getType());
    }
    
}