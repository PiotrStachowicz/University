public class Node<T> {
    private T value;
    public Node<T> next_node;
    public Node(T x) {
        value = x;
        next_node = null;
    }
    public T get_value() {
        return this.value;
    }
}
