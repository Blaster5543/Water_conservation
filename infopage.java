import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.Scanner;

public class infopage extends info implements ActionListener {

    JFrame frame = new JFrame();

    JButton BACK = new JButton("Back");
    JLabel Name = new JLabel("County Name");

    JLabel Population = new JLabel("Population");

    JLabel gallonsPerCapita = new JLabel("Gallons Per Capita ");

    JLabel avgGallonsPerResident = new JLabel("Average Resident water use");
    private JPanel background = new JPanel();
    int check = 0;

    JLabel pop = new JLabel();
    JLabel gal = new JLabel();
    JLabel galper = new JLabel();
    JLabel anvg = new JLabel();

    infopage(String s) throws FileNotFoundException {


        Name.setBounds (150,100,200,40);
        Font  f1  = new Font(Font.SANS_SERIF, Font.PLAIN,  15);
        Name.setFont(f1);
        frame.add(Name);

        Population.setBounds(150,200,200,40);
        Population.setFont(f1);
        frame.add(Population);

        gallonsPerCapita.setBounds(150,300,200,40);
        gallonsPerCapita.setFont(f1);
        frame.add(gallonsPerCapita);

        avgGallonsPerResident.setBounds(150,400,200,40);
        avgGallonsPerResident.setFont(f1);
        frame.add(avgGallonsPerResident);

        //pop gal galper avng
        pop.setBounds(150,150,200,40);
        pop.setFont(f1);
        frame.add(pop);

        gal.setBounds(150,250,200,40);
        gal.setFont(f1);
        frame.add(gal);

        galper.setBounds(150,350,200,40);
        galper.setFont(f1);
        frame.add(galper);

        anvg.setBounds(150,450,200,40);
        anvg.setFont(f1);
        frame.add(anvg);


        BACK.setBounds (0,0,100,40);
        BACK.setFocusable(false);
        BACK.addActionListener(this);
        frame.add(BACK);

        Border blackline = BorderFactory.createLineBorder(Color.black);
        background.setBounds(110,100,300,400);
        background.setBorder(blackline);
        frame.add(background);

        ImageIcon background = new ImageIcon("bock.jpg");
        Image img = background.getImage();
        Image temp = img.getScaledInstance(1023, 682, Image.SCALE_SMOOTH);
        background = new ImageIcon(temp);
        JLabel back = new JLabel(background);
        back.setLayout(null);
        back.setBounds(0, 0, 500, 600);

        frame.add(back);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 600);
        frame.setLayout(null);
        frame.setVisible(true);


        File file = new File("water_table.txt");
        Scanner input = new Scanner(file);

        while (input.hasNext()) {
            String word = input.next();

            if (s.equals(word) || s.equals(word + ",")) {
            check = 1;

            //pop gal galper avng

            word = word + " " + input.next();
            pop.setText(word);

            word = input.next();

            gal.setText(word);

            word = input.next();

            galper.setText(word);

            word = input.next();

            anvg.setText(word);


            }


        }
        if (check == 0) {
            System.out.println("No County Found, Try Again!");
        }

    }   public void actionPerformed(ActionEvent e) {
        if (e.getSource() == BACK) {
            frame.dispose();
            info one = new info();
    }
    }
}
