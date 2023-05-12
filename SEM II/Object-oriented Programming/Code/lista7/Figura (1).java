// Piotr Stachowicz Zadanie 1 lista 7
import javax.swing.*;
import java.awt.*;
import java.io.*;
public abstract class Figura implements Serializable {
    private String nazwa;
    private String typ;
    private String kolor;
    public Figura(){
        this.nazwa = "";
        this.typ = "";
        this.kolor = "";
    } // Konstruktor
    public Figura(String Nazwa, String Typ, String Kolor){
        this.nazwa = Nazwa;
        this.typ = Typ;
        this.kolor = Kolor;
    } // Konstruktor
    // Gettery i Settery
    public String getNazwa(){
        return nazwa;
    }
    public String getTyp(){
        return typ;
    }
    public String getKolor(){
        return kolor;
    }
    public void setNazwa(String nazwa1){
        this.nazwa = nazwa1;
    }
    public void setTyp(String typ1){
        this.typ = typ1;
    }
    public void setKolor(String kolor1){
        this.kolor = kolor1;
    }
    public abstract String toString();
    public abstract double ObliczPole();
    public abstract void saveToFile(Object object, String fileName);
}

class Okrag extends Figura implements Serializable{
    private int promien;
    public Okrag(String nazwa, String kolor, int promien) {
        super(nazwa, "Okrag", kolor);
        this.promien = promien;
    } // Konstruktor
    // Gettery i Settery
    public int getPromien(){
        return promien;
    }
    public void setPromien(int promien1){
        this.promien = promien1;
    }
    @Override
    public String toString() {
        return "Nazwa: " + getNazwa() + "\n" +
                "Typ: " + getTyp() + "\n" +
                "Pole: " + ObliczPole() + "\n" +
                "Promien: " + getPromien() + "\n";
    }
    @Override
    public double ObliczPole() {
        return Math.PI*(promien*promien);
    }
    public void saveToFile(Object object, String fileName) {
        try {
            FileOutputStream fos = new FileOutputStream(fileName);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(object);
            oos.close();
            fos.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    } // Write
}

class Trojkat extends Figura implements Serializable {
    private int a ,b ,c;
    public Trojkat(String nazwa, String kolor, int dlA, int dlB, int dlC) {
        super(nazwa, "Trojkat", kolor);
        this.a = dlA;
        this.b = dlB;
        this.c = dlC;
    } // Konstruktor
    // Gettery i Settery
    public int getA(){
        return this.a;
    }
    public int getB(){
        return this.b;
    }
    public int getC(){
        return this.c;
    }
    public void setA(int dlA){
        this.a = dlA;
    }
    public void setB(int dlB){
        this.b = dlB;
    }
    public void setC(int dlC){
        this.c = dlC;
    }
    @Override
    public String toString() {
        return "Nazwa: " + getNazwa() + "\n" +
                "Typ: " + getTyp() + "\n" +
                "Pole: " + ObliczPole() + "\n" +
                "Dlugosc A: " + getA() + "\n" +
                "Dlugosc B: " + getB() + "\n" +
                "Dlugosc C: " + getC() + "\n";
    }
    @Override
    public double ObliczPole() {
        int s = (getA() + getB() + getC())/2;
        return Math.sqrt(s*(s-getA())*(s-getB())*(s=getC()));
    }
    public void saveToFile(Object object, String fileName) {
        try {
            FileOutputStream fos = new FileOutputStream(fileName);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(object);
            oos.close();
            fos.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    } // Write
}

class OkragEditor extends JComponent {
    private final Okrag okrag;
    private final JTextField promienField;
    private final JTextField nazwaField;
    private final JTextField kolorField;
    private final JLabel poleField;
    public OkragEditor(Okrag okrag) {
        // Klasa Okrag i Layout
        this.okrag = okrag;
        setLayout(new BorderLayout());
        // Główny Panel
        JPanel fieldsPanel = new JPanel();
        fieldsPanel.setLayout(new GridLayout(5, 2));
        // Promień
        fieldsPanel.add(new JLabel("Promien:"));
        promienField = new JTextField(String.valueOf(okrag.getPromien()));
        fieldsPanel.add(promienField);
        // Nazwa
        fieldsPanel.add(new JLabel("Nazwa:"));
        nazwaField = new JTextField(String.valueOf(okrag.getNazwa()));
        fieldsPanel.add(nazwaField);
        // Kolor
        fieldsPanel.add(new JLabel("Kolor:"));
        kolorField = new JTextField(String.valueOf(okrag.getKolor()));
        fieldsPanel.add(kolorField);
        // Typ
        fieldsPanel.add(new JLabel("Typ:"));
        fieldsPanel.add(new JLabel(String.valueOf(okrag.getTyp())));
        // Pole Okregu
        fieldsPanel.add(new JLabel("Pole:"));
        poleField = new JLabel(String.valueOf((int)okrag.ObliczPole()));
        fieldsPanel.add(poleField);
        // Guzik Aktualizuj
        JButton updateButton = new JButton("Aktualizuj Okrag");
        updateButton.addActionListener(e -> {
            okrag.setPromien(Integer.parseInt(promienField.getText()));
            okrag.setNazwa(String.valueOf(nazwaField.getText()));
            okrag.setKolor(String.valueOf(kolorField.getText()));
            okrag.saveToFile(okrag, okrag.getNazwa() + ".ser");
            poleField.setText(String.valueOf((int)okrag.ObliczPole()));
        });
        add(fieldsPanel, BorderLayout.NORTH);
        add(updateButton, BorderLayout.SOUTH);
    }
} // Edytor do Okregu

class TrojkatEditor extends JComponent {
    private final Trojkat trojkat;
    private final JTextField aField;
    private final JTextField bField;
    private final JTextField cField;
    private final JTextField nazwaField;
    private final JTextField kolorField;
    private final JLabel poleField;
    public TrojkatEditor(Trojkat trojkat) {
        // Klasa Trojkat i Layout
        this.trojkat = trojkat;
        setLayout(new BorderLayout());
        // Główny Panel
        JPanel fieldsPanel = new JPanel();
        fieldsPanel.setLayout(new GridLayout(7, 2));
        // bok A
        fieldsPanel.add(new JLabel("Bok A:"));
        aField = new JTextField(String.valueOf(trojkat.getA()));
        fieldsPanel.add(aField);
        // bok B
        fieldsPanel.add(new JLabel("Bok B:"));
        bField = new JTextField(String.valueOf(trojkat.getB()));
        fieldsPanel.add(bField);
        // bok C
        fieldsPanel.add(new JLabel("Bok C:"));
        cField = new JTextField(String.valueOf(trojkat.getC()));
        fieldsPanel.add(cField);
        // Nazwa
        fieldsPanel.add(new JLabel("Nazwa:"));
        nazwaField = new JTextField(String.valueOf(trojkat.getNazwa()));
        fieldsPanel.add(nazwaField);
        // Kolor
        fieldsPanel.add(new JLabel("Kolor:"));
        kolorField = new JTextField(String.valueOf(trojkat.getKolor()));
        fieldsPanel.add(kolorField);
        // Typ
        fieldsPanel.add(new JLabel("Typ:"));
        fieldsPanel.add(new JLabel(String.valueOf(trojkat.getTyp())));
        // Pole Okregu
        fieldsPanel.add(new JLabel("Pole:"));
        poleField = new JLabel(String.valueOf((int)trojkat.ObliczPole()));
        fieldsPanel.add(poleField);
        JButton updateButton = new JButton("Aktualizuj Trojkat");
        updateButton.addActionListener(e -> {
            trojkat.setA(Integer.parseInt(aField.getText()));
            trojkat.setB(Integer.parseInt(bField.getText()));
            trojkat.setC(Integer.parseInt(cField.getText()));
            trojkat.setNazwa(nazwaField.getText());
            trojkat.setKolor(kolorField.getText());
            trojkat.saveToFile(trojkat,trojkat.getNazwa() + ".ser");
            poleField.setText(String.valueOf((int)trojkat.ObliczPole()));
        });
        add(fieldsPanel, BorderLayout.NORTH);
        add(updateButton, BorderLayout.SOUTH);
    }
} // Edytor do Trojkatow

class FiguryApp {
    public Object readFromFile(String fileName) {
        Object object = null;
        try {
            FileInputStream fis = new FileInputStream(fileName);
            ObjectInputStream ois = new ObjectInputStream(fis);
            object = ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
        return object;
    } // Read
    public static void main(String[] args) {
        if (args.length != 2 || !(args[1].equalsIgnoreCase("Okrag") || args[1].equalsIgnoreCase("Trojkat"))) {return;}
        String filename = args[0];
        String objectname = args[1];
        Figura figura;
        JFrame frame = new JFrame("Edytor do Figur");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(550, 230);
        JPanel panel = new JPanel();
        FiguryApp figuryApp = new FiguryApp();
        if (new File(filename).exists()) {
            if (objectname.equalsIgnoreCase("Okrag")) {
                figura = (Okrag) figuryApp.readFromFile(filename);
                panel.add(new OkragEditor((Okrag) figura));
            } else if (objectname.equalsIgnoreCase("Trojkat")) {
                figura = (Trojkat) figuryApp.readFromFile(filename);
                panel.add(new TrojkatEditor((Trojkat) figura));
            }
        } else {
            if (objectname.equalsIgnoreCase("Okrag")) {
                figura = new Okrag("Okrag Stonehenge", "Niebieski", 42);
                panel.add(new OkragEditor((Okrag) figura));
            } else if (objectname.equalsIgnoreCase("Trojkat")) {
                figura = new Trojkat("Trojkat Bermudzki", "Aqua", 1500, 1700, 1500); // Prawdziwe wymiary
                panel.add(new TrojkatEditor((Trojkat) figura));
            } else {
                return;
            }
        }
        frame.add(panel, BorderLayout.CENTER);
        frame.setVisible(true);
    }
}


