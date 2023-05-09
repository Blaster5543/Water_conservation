import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class Tips extends Yesnt implements ActionListener {

    JFrame frame = new JFrame();
    JTextArea title = new JTextArea("Some Personalized Tips based on responses.");

    JButton moreTips = new JButton("More Tips!");

    //present 3 tips. //button for more tips.
    JTextArea tip1 = new JTextArea();
    JTextArea tip2 = new JTextArea();
    JTextArea tip3 = new JTextArea();

    JTextArea tip5 = new JTextArea();
    int one = 1;

    JPanel background = new JPanel();

    Tips(String s) {
    for (int m = 0; m < 3; m ++ ) {
    char[] ch = s.toCharArray();

    Random r = new Random();
    int low = 1;
    int high = 14;
    int result = r.nextInt(high - low) + low;

    if (ch[result] == 'Y' && result % 2 == 0) {
      tip1.setText("Take at most 5 minute showers.");
      tip2.setText("Don't leave sinks running when shaving or brushing your teeth.");
       tip3.setText("Check for leaks inside your toilets, use food coloring if you aren't sure if there are leaks.");
        one = 1;
       } else if (ch[2] == 'N' ){
        tip1.setText("Install dripping sprinklers instead for your garden.");
        tip2.setText("Water your lawn in the morning or evening instead to reduce evaporation.");
        tip3.setText("Plant native plants to reduce the amount of water needed for watering.");
        one = 2;
         } else {
        m--;
     }
    }

        title.setBounds (150,150,200,40);
          frame.add(title);

        tip1.setBounds(150,300,200,30);
        tip2.setBounds(150,350,200,30);
        tip3.setBounds(150,400,200,30);
        tip5.setBounds(150,500,200,30);

        title.setLineWrap(true);
        title.setWrapStyleWord(true);
        title.setEditable(false);
        title.setOpaque(false);
        title.setBorder(new EmptyBorder(0, 0, 0, 0));

        tip1.setLineWrap(true);
        tip1.setWrapStyleWord(true);
        tip1.setEditable(false);
        tip1.setOpaque(false);
        tip1.setBorder(new EmptyBorder(0, 0, 0, 0));
        tip1.setColumns(3);

        tip2.setLineWrap(true);
        tip2.setWrapStyleWord(true);
        tip2.setEditable(false);
        tip2.setOpaque(false);
        tip2.setBorder(new EmptyBorder(0, 0, 0, 0));
        tip2.setColumns(3);

        tip3.setLineWrap(true);
        tip3.setWrapStyleWord(true);
        tip3.setEditable(false);
        tip3.setOpaque(false);
        tip3.setBorder(new EmptyBorder(0, 0, 0, 0));
        tip3.setColumns(3);

        moreTips.setBounds (150,200,200,40);
        moreTips.setFocusable(false);
        moreTips.addActionListener(this);

        frame.add(moreTips);


        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 600);
        frame.setLayout(null);
        frame.setVisible(true);

        frame.add(tip1);
        frame.add(tip2);
        frame.add(tip3);



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


    }


    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == moreTips) {
         frame.dispose();
          moreTips clown = new moreTips(one);
        }
    }
}

