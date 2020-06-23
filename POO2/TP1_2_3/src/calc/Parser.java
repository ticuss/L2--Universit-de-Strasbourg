package calc;

public class Parser {
    private static String src;
    private static int idx;

    private static char last_char;
    private static int last_cst;

    private static boolean read_char(char c) {
        if ((idx < src.length()) && (src.charAt(idx) == c)) {
            idx++;
            last_char = c;
            return true;
        }
        return false;
    }

    private static boolean read_cst() {
        boolean res = false;
        while (idx < src.length() && Character.isDigit(src.charAt(idx))) {
            if (!res)
                last_cst = 0;
            res = true;
            last_cst = last_cst * 10 + Character.getNumericValue(src.charAt(idx));
            idx += 1;
        }
        ;
        return res;
    }

    private static EXPR read_e() {
        EXPR result, right;
        char op;
        result = read_e_mul();
        if (result != null) {
            while (read_char('+') || read_char('-')) {
                op = last_char;
                right = read_e_mul();
                if (right == null)
                    error();
                if (op == '+')
                    result = new Adition(result, right);
                else
                    result = new Minus(result, right);
            }
        }
        return result;
    }

    private static EXPR read_e_mul() {
        EXPR result, right;
        char op;
        result = read_e_unary();
        if (result != null) {
            while (read_char('*') || read_char('/')) {
                op = last_char;
                right = read_e_unary();
                if (right == null)
                    error();
                if (op == '*')
                    result = new Multiplication(result, right);
                else
                    result = new Division(result, right);
            }
        }
        return result;
    }

    private static EXPR read_e_unary() {
        EXPR result;
        char op;
        if (read_char('+') || read_char('-')) {
            op = last_char;
            result = read_e_unary();
            if (result == null)
                error();
            if (op == '-')
                result = new Negation(result);
        }
        else
            result = read_e_cst();
        return result;
    }

    private static EXPR read_e_cst() {
        EXPR result = null;
        if (read_char('(')) {
            result = read_e();
            if (result == null)
                error();
            if (!read_char(')'))
                error();
        }
        else if(read_cst())
            result = new Const(last_cst);
        return result;
    }

    private static void error() {
        int j;
        System.out.println(src);
        for (j = 0; j < idx; j++)
            System.out.print(' ');
        System.out.println('I');
        System.exit(1);
    }

    static EXPR parse_on(String txt) {
        EXPR e;
        src = txt;
        idx = 0;
        e = read_e();
        if ((e == null) || (idx < src.length()))
            error();
        return e;
    }
    
    public static void main(String[] args) {
        String[] toCalc = new String[] { "2+3*5-4*-4*5+20+30+50" };
        System.out.println(toCalc[0]+" = ??? ");
        Calc.main(toCalc);
    }
    
    
    
    
    
    
}