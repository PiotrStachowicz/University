using System;
//Piotr Stachowicz
//Zadanie 2 lista 3
//JetBrains Rider
public class Node<T>
{
    public T value;
    public Node<T> NextNode;
    public Node<T> PrevNode;

    public Node(T Value)
    {
        this.value = Value;
    }
}
public class Lista<T>
{
    public Node<T> Head;
    public Node<T> Tail;
    //front rozumiem jako głowe listy
    public void push_front(T elem)
    {
        Node<T> NewNode = new Node<T>(elem);
        if (Head != null)
        {
            this.Head.NextNode = NewNode;
            NewNode.PrevNode = this.Head;
            this.Head = NewNode;
        }
        else
        {
            Head = NewNode;
            Tail = NewNode;
        }
    }
    public void push_back(T elem)
    {
        Node<T> NewNode = new Node<T>(elem);
        if (Tail != null)
        {
            this.Tail.PrevNode = NewNode;
            NewNode.NextNode = this.Tail;
            this.Tail = NewNode;
        }
        else
        {
            Head = NewNode;
            Tail = NewNode;
        }
    }

    public bool is_empty()
    {
        //nie ma głowy nie ma listy
        return Head == null;
    }

    public T pop_front()
    {
        if (is_empty())
        {
            throw new Exception("Nie mozna wykonac operacji!");
        }
        else
        {
            T return_value = this.Tail.value;
            if (Head == Tail)
            {
                Head = null;
                Tail = null;
                return return_value;
            }
            this.Head = Head.PrevNode;
            return return_value;
        }
    }
    public T pop_back()
    {
        if (is_empty())
        {
            throw new Exception("Nie mozna wykonac operacji!");
        }
        else
        {
            T return_value = this.Tail.value;
            if (Head == Tail)
            {
                Head = null;
                Tail = null;
                return return_value;
            }
            this.Tail = Tail.NextNode;
            return return_value;
        }
    }
}