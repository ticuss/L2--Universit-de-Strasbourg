package calc;

public class Division extends EXPR_BINARY{
    Division( EXPR l, EXPR r ) {
        left=l;
        right=r;
    }
    public int eval() {
        return left.eval() / right.eval();
    }
}