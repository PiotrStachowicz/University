import java.io.*;
//Piotr Stachowicz
//Lista 6
public class Main {
    public static void main(String[] args) throws IOException {
        Buffer<Integer> buffer = new Buffer<>();
        Buffer<Integer> buffer2 = new Buffer<>();
        buffer.add(1);
        buffer.add(2);
        buffer.add(3);
        buffer2.add(4);
        buffer2.add(5);
        buffer2.add(6);
        try {
            // Zapisanie buffora 1 i 2 w pliku Object.txt
            FileOutputStream fos = new FileOutputStream(new File("Object.txt"));
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(buffer);
            oos.writeObject(buffer2);
            oos.close();
            fos.close();
            // Odczytywanie buffora 1 i 2 z pliku Object.txt
            FileInputStream fis = new FileInputStream(new File("Object.txt"));
            ObjectInputStream ois = new ObjectInputStream(fis);
            Buffer<Integer> copied_buff = (Buffer<Integer>) ois.readObject();
            Buffer<Integer> copied_buff2 = (Buffer<Integer>) ois.readObject();
            fis.close();
            ois.close();
            copied_buff.print();
            copied_buff2.print();
        }catch (FileNotFoundException e) {
            System.out.println("File not found");
        } catch (IOException e) {
            System.out.println("Error initializing stream");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

    }
}