package calc;

public class Negation extends EXPR_UNARY{
    Negation( EXPR v ) {
        arg=v;
    }
    public int eval() {
        return -arg.eval();
    }
}