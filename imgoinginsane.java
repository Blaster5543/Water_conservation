import java.awt.GridBagConstraints;
import java.awt.event.ActionListener;
import java.awt.*;
import java.awt.event.*;
import javax.swing.JFrame;
import javax.swing.*;
import javax.swing.UIManager;
import javax.swing.border.Border;
//flatpak
public class imgoinginsane extends JFrame implements  ActionListener {
    JFrame frame = new JFrame();
    JButton START = new JButton ("Begin Program");
    JButton EXIT = new JButton ("Exit Program");
    JPanel background = new JPanel();
    JLabel WELCOME =  new JLabel( "A Simple Water Calculator");

    imgoinginsane() {
        setTitle("Water Project");

        WELCOME.setBounds(150, 200, 200,40);
        Font  f1  = new Font(Font.SANS_SERIF, Font.PLAIN,  16);
        WELCOME.setFont(f1);
        frame.add(WELCOME);
        WELCOME.setVisible(true);

        START.setBounds(150,240,200,40);
        START.setFocusable(false);

        EXIT.setBounds(150,300,200,40);
        EXIT.setFocusable(false);

        frame.add(WELCOME);
        frame.add(EXIT);
        frame.add(START);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500,600);
        frame.setLayout(null);
        frame.setVisible(true);

        START.addActionListener(this);
        EXIT.addActionListener(this);

        Border blackline = BorderFactory.createLineBorder(Color.black);
        background.setBounds(110,100,300,400);
        background.setBorder(blackline);
        frame.add(background);

        ImageIcon background = new ImageIcon("tock.jpg");
        Image img = background.getImage();
        Image temp = img.getScaledInstance(1023, 682, Image.SCALE_SMOOTH);
        background = new ImageIcon(temp);
        JLabel back = new JLabel(background);
        back.setLayout(null);
        back.setBounds(0, 0, 500, 600);

        frame.add(back);

        };

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == START) {
            dispose(); //bug
            frame.dispose();
            frame.disable();
            frame.setVisible(false);
            mainPage myPage = new mainPage();


        }
         else if (e.getSource() == EXIT) {

            System.exit(0);
        }
    }

    public static void main(String[] args) {
        try {
              UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
           // UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
        } catch(Exception e){
            System.out.println("L&F failed!");
        }
        new imgoinginsane();
    }
}

