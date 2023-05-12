using System;
//Piotr Stachowicz
//Lista 2 Zadanie 1 (IntStream)
void Main()
{
    //Pierwsza część zadania
    IntStream stream = new IntStream();
    Console.Write("{0} {1} {2}\n", stream.next(),stream.next(),stream.next()); // 0 1 2
    stream.reset();
    Console.Write("{0}\n", stream.next()); // 0
    //Druga część zadania
    PrimeStream ps = new PrimeStream();
    for (int i = 0; i < 5; i++)
    {
        Console.Write("{0}\n", ps.next()); // 2 3 5 7 11
    }
    //Trzecia część zadania
    RandomStream rs = new RandomStream();
    for (int i = 0; i < 5; i++)
    {
        Console.Write("{0}\n", rs.next());
    }
    //Czwarta część zadania
    RandomWordStream rws = new RandomWordStream();
    for (int i = 0; i < 5; i++)
    {
        Console.Write(rws.next());
        if(i==3) rws.reset();
    }
}
Main();
class IntStream
{
    private int Value = -1;
    public virtual int next()
    {
        if (eos())
        {
            throw new Exception("End of stream!");
        }
        Value++;
        return Value;
    }
    public virtual bool eos()
    {
        if (Value == Int32.MaxValue)
        {
            return true;
        }
        return false;
    }
    public virtual void reset()
    {
        Value = -1;
    }

}

class PrimeStream : IntStream
{
    private int PrimeValue;
    public override int next()
    {
        PrimeValue = PrimeGenerator();
        return PrimeValue;
    }
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
    private int PrimeGenerator()
    {
        for (int j = PrimeValue; true; j++)
        {
            if (eos())
            {
                throw new Exception("End of stream!");
            }
            if (IsPrime(j) && j != PrimeValue) return j;
        }
    }
    public override bool eos()
    {
        if (PrimeValue == Int32.MaxValue)
        {
            return true;
        }

        int Copy = PrimeValue;
        while (!IsPrime(Copy+1))
        {
            if (Copy == Int32.MaxValue) return true;
            Copy++;
        }
        return false;
    }
    public override void reset()
    {
        PrimeValue = 0;
    }
}

class RandomStream : IntStream
{
    private int RandomValue;
    private readonly Random random = new Random();
    public override int next()
    {
        if (eos())
        {
            throw new Exception("End of stream!");
        }
        RandomValue = random.Next(Int32.MaxValue);
        return RandomValue;
    }
    public override bool eos()
    {
        return false;
    }
    public override void reset()
    {
        RandomValue = 0;
    }
}

class RandomWordStream
{
    private int Length;
    private readonly PrimeStream ps = new PrimeStream();
    private readonly RandomStream rs = new RandomStream();

    public string next()
    {
        if (eos())
        {
            throw new Exception("End of stream!");
        }
        Length = ps.next();
        string str = "";
        for (int i = 0; i < Length; i++)
        {
            char a = (char)((rs.next() % 26) + 'a');
            str += a;
        }

        str += '\n';
        return str;
    }
    public bool eos()
    {
        if (Length == Int32.MaxValue)
        {
            return true;
        }

        int Copy = Length;
        while (!ps.IsPrime(Copy+1))
        {
            if (Copy == Int32.MaxValue) return true;
            Copy++;
        }
        return false;
    }
    public void reset()
    {
        ps.reset();
        rs.reset();
        Length = 0;
    }
}