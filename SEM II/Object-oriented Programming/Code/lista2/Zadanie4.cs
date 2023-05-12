using System;
using System.Collections.Generic;
//Piotr Stachowicz
//Lista 2 Zadanie 4 (LazyList)
void Main()
{
    //Pierwsza część zadania
    var lista = new LazyIntList();
    var lista2 = new LazyPrimeList();
    Console.Write("Element index:{0} value:{1} \n", 40, lista.Element(40));
    Console.Write("List length: {0} \n", lista.Size());
    Console.Write("Element index:{0} value:{1} \n", 38, lista.Element(38));
    Console.Write("List length: {0} \n", lista.Size());
    Console.Write("Element index:{0} value:{1} \n", 40, lista.Element(40));
    Console.Write("List length: {0} \n", lista.Size());
    //Druga część zadania
    Console.Write("Element index:{0} value:{1} \n", 5, lista2.Element(5));
    Console.Write("List length: {0} \n", lista2.Size());
    Console.Write("Element index:{0} value:{1} \n", 3, lista2.Element(3));
    Console.Write("List length: {0} \n", lista2.Size());
    Console.Write("Element index:{0} value:{1} \n", 5, lista2.Element(5));
    Console.Write("List length: {0} \n", lista2.Size());
}
Main();
class LazyIntList
{
    protected List<int> MyList = new List<int>();
    private int size;
    public virtual int Size()
    {
        return size;
    }
    public virtual int Element(int i)
    {
        if (i <= size) return MyList[i-1];
        for (var elem = size+1; elem <= i; elem++)
        {
            MyList.Add(elem);
            size++;
        }
        return MyList[i-1];
    }
}
class LazyPrimeList : LazyIntList
{
    protected List<int> MyPrimeList = new List<int>();
    private int Primesize;
    private bool IsPrime(int number)
    {
        if (number <= 1) return false;
        if (number <= 3) return true;
        if (number % 2 == 0 || number % 3 == 0) return false;
        for (int i = 5; i * i <= number; i += 6)
        {
            if (number % i == 0 || number % (i + 2) == 0) return false;
        }
        return true;
    }
    private int PrimeGenerator(int i)
    {
        int count = 0;
        for (int j = 1; true; j++)
        {
            if (IsPrime(j))
            {
                count++;
                if (count == i) return j;
            }
        }
    }
    public override int Element(int i)
    {
        if (i <= Primesize) return MyList[i-1];
        for (var elem = Primesize+1; elem <= i; elem++)
        {
            MyList.Add(PrimeGenerator(elem));
            Primesize++;
        }
        return MyList[i-1];
    }
    public override int Size()
    {
        return Primesize;
    }
}