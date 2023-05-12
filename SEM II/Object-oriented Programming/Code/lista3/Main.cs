using System;
public class Run
{
    public static void Main()
    {
        Lista<int> lista = new Lista<int>();
        lista.push_front(2);
        lista.push_front(3);
        lista.push_back(1);
        lista.push_back(0);
        //0<->1<->2<->3
        lista.pop_front();
        //0<->1<->2
        Console.WriteLine("Head: {0}", lista.Head.value);
        lista.pop_back();
        //1<->2
        Console.WriteLine("Tail: {0}", lista.Tail.value);
        lista.pop_back();
        lista.pop_back();
        if(lista.is_empty()) Console.WriteLine("Lista jest pusta!");
    }
}