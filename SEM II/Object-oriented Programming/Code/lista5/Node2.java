class Add extends Expression {
    //Chcemy mieć po lewej i prawej coś na czym możemy użyć evaluate i tostring
    Expression left;
    Expression right;
    public Add(Expression l, Expression r){
        left = l;
        right = r;
    }
    @Override
    public int evaluate() {
        return left.evaluate() + right.evaluate();
    }
    @Override
    public String toString() {
        return "(" + left.toString() + "+" + right.toString() + ")";
    }
}
class Multiplication extends Expression {
    Expression left;
    Expression right;
    public Multiplication(Expression l, Expression r){
        left = l;
        right = r;
    }
    @Override
    public int evaluate() {
        return left.evaluate() * right.evaluate();
    }

    @Override
    public String toString() {
        return "(" + left.toString() + "*" + right.toString() + ")";
    }
}
class Divide extends Expression {
    Expression left;
    Expression right;
    public Divide(Expression l, Expression r){
        left = l;
        right = r;
    }
    @Override
    public int evaluate() {
        return left.evaluate() / right.evaluate();
    }

    @Override
    public String toString() {
        return "(" + left.toString() + "/" + right.toString() + ")";
    }
}