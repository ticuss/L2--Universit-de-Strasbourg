package calc;

public class Calc {
    public static void main(String[] args) {
        EXPR e;
        e = Parser.parse_on(args[0]);
        System.out.println("Resultat : " + e.eval());
        
    }
}