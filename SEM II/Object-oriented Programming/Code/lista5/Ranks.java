public class Ranks implements Comparable<Ranks>{
    public int rank; // Diamond-10 , Platinum-7 , Gold-5, Silver-2
    public int getRank(){
        return rank;
    }
    public String toString(){
        return String.valueOf(rank);
    }
    @Override
    public int compareTo(Ranks o) {
        return Integer.compare(this.rank,o.rank);
    }
}
class Diamond extends Ranks {
    public Diamond(){
        this.rank = 10;
    }
}
class Platinum extends Ranks {
    public Platinum(){
        this.rank = 7;
    }
}
class Gold extends Ranks {
    public Gold(){
        this.rank = 5;
    }
}
class Silver extends Ranks {
    public Silver(){
        this.rank = 2;
    }
}