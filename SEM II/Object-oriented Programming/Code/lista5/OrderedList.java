public class OrderedList<T extends Comparable<T>> {
    private Node<T> node;
    public OrderedList(){
        node = null;
    }
    public OrderedList(T x){
        node = new Node<T>(x);
    }
    public T get_first() throws Exception {
        if(node==null) {
            throw new Exception("node was null");
        }
        return node.get_value();
    }
    public T get_last() throws Exception {
        if(node==null) {
            throw new Exception("node was null");
        }
        Node<T> first = node;
        while (node.next_node!=null){
            node = node.next_node;
        }
        T x = node.get_value();
        node = first;
        return x;
    }
    public void add(T x){
        Node<T> new_node = new Node<T>(x);
        if(node==null){
            node = new_node;
            return;
        }
        Node<T> first = node;
        if(x.compareTo(node.get_value()) < 0){
            node = new_node;
            new_node.next_node = first;
            return;
        }
        while (node.next_node!=null && (x.compareTo(node.next_node.get_value()) > 0 || x.compareTo(node.get_value()) < 0)){
            node = node.next_node;
        }
        if (node.next_node != null) {
            new_node.next_node = node.next_node;
        }
        node.next_node = new_node;
        node = first;
    }
    public String to_String() {
        StringBuilder string = new StringBuilder();
        Node<T> first = node;
        while (node!=null){
            T x = node.get_value();
            string.append(x.toString()).append(" \n");
            node = node.next_node;
        }
        node = first;
        return string.toString();
    }
}

