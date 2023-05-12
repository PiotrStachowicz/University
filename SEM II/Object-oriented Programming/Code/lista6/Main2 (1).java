import java.io.*;
//Piotr Stachowicz
//Lista 6
public class Main2 {
    public static void main(String[] args) throws IOException {
        Buffer2<String> buffer = new Buffer2<>();
        Producent Kaufland = new Producent(buffer);
        Konsument Kowalski = new Konsument(buffer);
        Thread thread1 = new Thread(Kaufland);
        Thread thread2 = new Thread(Kowalski);
        // Kaufland cały czas wystawia mleko na półki aż ich nie przepełni, wtedy czeka i po jakimś czasie
        //jak kowalski skończy zakupy, zaczyna prace od nowa...
        thread1.start();
        thread2.start();
    }
}