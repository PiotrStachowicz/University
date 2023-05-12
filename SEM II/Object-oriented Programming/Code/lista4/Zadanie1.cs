using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection.Emit;
//Piotr Stachowicz
//Zadanie 1 Lista 4
void Main()
{
    LazyIntList lazyIntList= new LazyIntList();
    LazyPrimeList lazyPrimeList = new LazyPrimeList();
    foreach (var e in lazyPrimeList)
    {
        Console.Write("{0} \n", e);
    }
    //To według mojej implementacji wypisuje:
    //2
    //3
    //5
    //...
}
Main();
public interface ListCollection
{
    int Size();
    int Element(int i);
}

public class LazyIntList : ListCollection
{
    private List<int> MyList = new List<int>();
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
public class LazyPrimeList : ListCollection, IEnumerable
{
    public List<int> MyPrimeList = new List<int>();
    private int Primesize;
    public bool IsPrime(int number)
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
    public int PrimeGenerator(int i)
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
    public int Element(int i)
    {
        if (i <= Primesize) return MyPrimeList[i-1];
        for (var elem = Primesize+1; elem <= i; elem++)
        {
            MyPrimeList.Add(PrimeGenerator(elem));
            Primesize++;
        }
        return MyPrimeList[i-1];
    }
    public int Size()
    {
        return Primesize;
    }
    public int this[int idx] {
        get
        {
            return this.MyPrimeList[idx];
        }
    }

    public int Lenght
    {
        get
        {
            return MyPrimeList.Count;
        }
    }

    public override string ToString()
    {
        return String.Format("Last prime number is: {0}", this[Primesize-1]);
    }

    public IEnumerator GetEnumerator()
    {
        return new LazyPrimeListEnumerator(this);
    }
}


public class LazyPrimeListEnumerator : IEnumerator
{
    private LazyPrimeList _primeList;
    private int size;
    public LazyPrimeListEnumerator(LazyPrimeList lazyPrimeList)
    {
        this._primeList = lazyPrimeList;
    }

    public bool MoveNext()
    {
        _primeList.Element(size + 1);
        size += 1;
        return true;
    }

    public void Reset()
    {
        size = 0;
    }

    public object Current {
        get
        {
            return _primeList[size-1];
        }
    }
}