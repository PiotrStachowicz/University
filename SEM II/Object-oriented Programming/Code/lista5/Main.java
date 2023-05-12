public class Main {
    public static void main(String[] args) {
        OrderedList<Ranks> ranklist = new OrderedList<>();
        Diamond diamond = new Diamond();
        Silver silver = new Silver();
        Gold gold = new Gold();
        Platinum platinum = new Platinum();
        ranklist.add(diamond);
        ranklist.add(gold);
        ranklist.add(platinum);
        ranklist.add(silver);
        ranklist.add(diamond);
        //Lista "rosnąca" (według rang) Silver->Gold->Platinum->Diamond->Diamond
        //Innaczej 2 5 7 10 10 (według współczynnika dla rang)
        System.out.println(ranklist.to_String());
        OrderedList<Integer> list = new OrderedList<>();
        for (int i = 42;i>=0;i--){
            list.add(i);
        }
        //Ponownie, lista rosnąca 0 1 2...42
        System.out.println(list.to_String());
    }
}
//Piotr Stachowicz
//Lista 5 zadanie 1