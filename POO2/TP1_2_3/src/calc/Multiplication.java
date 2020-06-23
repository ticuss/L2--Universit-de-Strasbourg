package calc;

public class Multiplication extends EXPR_BINARY{
    Multiplication( EXPR l, EXPR r ) {
        left=l;
        right=r;
    }
    public int eval() {
        return left.eval() * right.eval();
    }
}