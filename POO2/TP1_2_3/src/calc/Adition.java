package calc;

public class Adition extends EXPR_BINARY{
	Adition( EXPR l, EXPR r ) {
        left=l;
        right=r;
    }
    public int eval() {
        return left.eval() + right.eval();
    }
}