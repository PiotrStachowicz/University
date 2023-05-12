using System;
using System.Collections;
//Piotr Stachowicz
//Zadanie 2 lista 4
void Main()
{
    SlowaFibonacciego sf = new SlowaFibonacciego(10);
    foreach (var i in sf)
    {
        Console.Write(i + "\n");
    }
    foreach (var i in sf)
    {
        Console.Write(i + "\n");
    }
}
Main();

public class SlowaFibonacciego : IEnumerable
{
    private int n;
    public SlowaFibonacciego(int x)
    {
        this.n = x;
    }

    public IEnumerator GetEnumerator()
    {
        return new FibEnumerator(n);
    }
}

public class FibEnumerator : IEnumerator
{
    private int currint = 0;
    private string fn1 = "a";
    private string fn2 = "b";
    private int n;

    public FibEnumerator(int x)
    {
        this.n = x;
    }
    public object Current
    {
        get
        {
            if(currint == 1) return "b";
            if (currint == 2) return "a";
            return fn1 + fn2;
        }
    }
    public bool MoveNext()
    {
        if (currint > 2)
        {
            string curr = fn1 + fn2;
            fn2 = fn1;
            fn1 = curr;
            if (currint >= n) return false;
        }
        currint++;
        return true;
    }

    public void Reset()
    {
        fn1 = "a";
        fn2 = "b";
        currint = 0;
    }
}