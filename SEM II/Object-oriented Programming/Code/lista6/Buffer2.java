import java.util.LinkedList;
public class Buffer2<T> extends Thread{
    private final LinkedList<T> buff;
    public final int bufferLength;
    public Buffer2(int BufferLength){
        buff = new LinkedList<>();
        bufferLength = BufferLength;
    }
    public boolean isFull(){
        return (buff.size() == bufferLength);
    }
    public boolean isEmpty(){
        return buff.isEmpty();
    }
    public synchronized void add(T item){
        while(isFull()){
            try {
                wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        buff.add(item);
        notify();
    }
    public synchronized T remove(){
        while(isEmpty()){
            try {
                wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        T item = buff.removeFirst();
        notify();
        return item;
    }
    public void print(){
        for (T t : buff) {
            System.out.println(t);
        }
    }
}
class Producent implements Runnable{
    Buffer2<String> buffer;
    public Producent(Buffer2<String> stringBuffer){
        this.buffer = stringBuffer;
    }
    @Override
    public void run() {
        int i = 1;
        while (true){
            buffer.add("Mleko" + i);
            System.out.println("Kaufland wyprodukował Mleko: " + i);
            i++;
            if(i>=buffer.bufferLength){
                i = 1;
            }
        }
    }
}
class Konsument implements Runnable{
    Buffer2<String> buffer;
    public Konsument(Buffer2<String> stringBuffer){
        this.buffer = stringBuffer;
    }
    @Override
    public void run() {
        while (true){
            String item = buffer.remove();
            System.out.println("Kowalski kupił:" + item);
        }
    }
}