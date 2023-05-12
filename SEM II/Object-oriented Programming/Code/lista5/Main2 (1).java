public class Main2 {
    public static void main(String[] args) {
        Expression expression1 = new Add(new Cons(4), new variable("x", 8));
        Expression expression2 = new Multiplication(expression1, new Cons(2));
        Expression expression3 = new Divide(expression2, new Cons(3));
        System.out.println(expression3 + "=" + expression3.evaluate());
        Expression expression4 = new Multiplication(new Cons(42), new variable("z", 3));
        Expression expression5 = new Divide(expression4, new Cons(2));
        Expression expression6 = new Add(expression5, new Cons(2023));
        System.out.println(expression6 + "=" + expression6.evaluate());
    }
}
//Piotr Stachowicz
//Lista 5 zadanie 2