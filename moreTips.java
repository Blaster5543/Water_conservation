import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class moreTips implements ActionListener {

    JFrame frame = new JFrame();
    private  JButton BACK = new JButton("back");

    JTextArea title = new JTextArea("More tips");

    JTextArea tip4 = new JTextArea();

    JTextArea tip5 = new JTextArea();

    JTextArea tip6 = new JTextArea();

    JPanel background = new JPanel();


    moreTips(int s) {

        if (s == 1) {
            tip4.setText("Do not constantly flush the toilets when disposing of small objects.");
            tip5.setText("Install low-flow faucets to save more water.");
            tip6.setText("Fill tubs half full instead if you need to bathe.");
        } else if (s == 2) {
            tip4.setText("Put mulch around trees and plants to reduce water evaporation.");
            tip5.setText("Recycle indoor water to water your plants instead.");
            tip6.setText("Only water your lawn if the grass does not spring back up after stepping on it.");
        }


        title.setLineWrap(true);
        title.setWrapStyleWord(true);
        title.setEditable(false);
        title.setOpaque(false);
        title.setBorder(new EmptyBorder(0, 0, 0, 0));
        frame.add(title);
        tip5.setBounds(150, 200, 200, 30);


        tip4.setBounds(150, 300, 200, 30);
        tip4.setLineWrap(true);
        tip4.setWrapStyleWord(true);
        tip4.setEditable(false);
        tip4.setOpaque(false);
        tip4.setBorder(new EmptyBorder(0, 0, 0, 0));
        tip4.setColumns(3);


        frame.add(tip4);
        tip5.setLineWrap(true);
        tip5.setWrapStyleWord(true);
        tip5.setEditable(false);
        tip5.setOpaque(false);
        tip5.setBorder(new EmptyBorder(0, 0, 0, 0));
        tip5.setColumns(3);
        frame.add(tip5);


        BACK.setBounds (0,0,100,40);
        BACK.setFocusable(false);
        BACK.addActionListener(this);

        tip6.setBounds(150,400,200,30);
        tip6.setLineWrap(true);
        tip6.setWrapStyleWord(true);
        tip6.setEditable(false);
        tip6.setOpaque(false);
        tip6.setBorder(new EmptyBorder(0, 0, 0, 0));
        tip6.setColumns(4);
        frame.add(tip6);

        BACK.setBounds (0,0,100,40);
        BACK.setFocusable(false);
        BACK.addActionListener(this);
        frame.add(BACK);


        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 600);
        frame.setLayout(null);
        frame.setVisible(true);


        Border blackline = BorderFactory.createLineBorder(Color.black);
        background.setBounds(110, 100, 300, 400);
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
        if (e.getSource() == BACK) {
            frame.dispose();
            mainPage two = new mainPage();

    }
    }
}
