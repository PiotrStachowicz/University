class Cons extends Expression {
    private final int constant;
    Cons(int x){
        constant = x;
    }
    @Override
    public int evaluate() {
        return constant;
    }

    @Override
    public String toString() {
        return String.valueOf(constant);
    }
}
class variable extends Expression{
    private final String var;
    private final int val;
    public variable(String name, int value){
        var = name;
        val = value;
    }
    @Override
    public int evaluate() {
        return val;
    }

    @Override
    public String toString() {
        return var;
    }
}
