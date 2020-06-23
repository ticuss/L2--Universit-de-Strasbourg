package calc;

public class Const extends EXPR{
    int value;
    
    public Const(int v) {
        value=v;
    }

    public Const(EXPR v) {
        value=v.eval();
    }

    public int eval() {
        return value;
    }
}