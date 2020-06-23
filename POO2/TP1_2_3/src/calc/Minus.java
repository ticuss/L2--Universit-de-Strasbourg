package calc;

public class Minus extends EXPR_BINARY{
	Minus( EXPR l, EXPR r ) {
        left=l;
        right=r;
    }
    public int eval() {
        return left.eval() - right.eval();
    }
}