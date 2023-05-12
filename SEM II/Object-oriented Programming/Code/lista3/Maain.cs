using System;
public class Maain
{
    public static void Main()
    {
        MyDictionary<int, int> myDictionary = new MyDictionary<int, int>();
        myDictionary.Add(1, 1);
        myDictionary.Add(2, 2);
        myDictionary.Add(3, 3);
        myDictionary.Add(4, 4);
        Console.WriteLine("{0}", myDictionary.node.next_node.next_node.next_node.value);
        //1->2->3->4
        myDictionary.Remove(1);
        myDictionary.Remove(3);
        //2->4
        Console.WriteLine("Klucz: {0} Wartosc: {1}", 2 ,myDictionary.Find(2));
    }
}