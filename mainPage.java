import java.awt.*;
import java.awt.event.*;
import javax.swing.JFrame;
import javax.swing.*;
import javax.swing.border.Border;

class mainPage extends imgoinginsane {

    private   JFrame frame = new JFrame();

    private   JPanel background = new JPanel();
    private  JLabel title = new JLabel("Select a function");
    private  JButton BACK = new JButton("back");
    private   JButton Survey = new JButton("User Survey");

    private    JButton Yesnt = new JButton("Simplified Survey");

    private    JButton countyInfo = new JButton("Information");

     mainPage() {

         Border blackline = BorderFactory.createLineBorder(Color.black);

         title.setBounds (180,200,200,40);
         Font  f1  = new Font(Font.SANS_SERIF, Font.PLAIN,  18);
         title.setFont(f1);
         frame.add(title);


         Yesnt.setBounds(180,370,200,40);
         Yesnt.addActionListener(this);

         countyInfo.setBounds(180,320,200,40);
         countyInfo.setFocusable(false);
         countyInfo.addActionListener(this);

         Survey.setBounds(180,270,200,40);
         Survey.setFocusable(false);
         Survey.addActionListener(this);

         BACK.setBounds (0,0,100,40);
         BACK.setFocusable(false);
         BACK.addActionListener(this);

         frame.add(Survey);
         frame.add(BACK);
         frame.add(Yesnt);
         frame.add(countyInfo);

         background.setBounds(140,100,300,400);
         background.setBorder(blackline);
         frame.add(background);

         frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         frame.setSize(500, 600);
         frame.setLayout(null);
         frame.setVisible(true);

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
         if (e.getSource() == Survey) {
            frame.dispose();
             Survey one = new Survey();
         } if (e.getSource() == BACK) {
            imgoinginsane one = new imgoinginsane();

         } if (e.getSource() == Yesnt) {
             frame.dispose();
             Yesnt one = new Yesnt();
         }  if (e.getSource() == countyInfo) {
             info one = new info();
         }
     }
 }
