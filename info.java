import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class info implements ActionListener {

    private  JFrame frame = new JFrame();
    private  JPanel background = new JPanel();

    private   JTextArea Question = new JTextArea("Search for County name here");

    private JTextArea Response = new JTextArea();
    private JButton Submit = new JButton("Enter");

     private JButton BACK = new JButton("Back");

    public JPanel picture = new JPanel(); //picture here

    public String countyName;

    public String getcountyName() {
        return countyName;
    }

    public void setCountyName(String countyName) {
        this.countyName = countyName;
    }

    info() {
        BACK.setBounds(0, 0, 100, 40);
        BACK.setFocusable(false);
        BACK.addActionListener(this);
        frame.add(BACK);

        Question.setBounds(150, 180, 200, 60);
        Font f1 = new Font(Font.SANS_SERIF, Font.PLAIN, 16);
        Question.setFont(f1);
        Question.setLineWrap(true);
        Question.setWrapStyleWord(true);
        Question.setEditable(false);
        Question.setOpaque(false);
        Question.setBorder(new EmptyBorder(0, 0, 0, 0));
        frame.add(Question);




        Response.setBounds(120, 280, 150, 40);
        frame.add(Response);

        Submit.setBounds(300, 280, 100, 20);
        Submit.addActionListener(this);
        frame.add(Submit);

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


        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 600);
        frame.setLayout(null);
        frame.setVisible(true);
        frame.getRootPane().setDefaultButton(Submit);
    }


    @Override
    public void actionPerformed(ActionEvent e) {

       if (e.getSource() == Submit) {
           String searchQuery = Response.getText();
           setCountyName(searchQuery);

           try {
               infopage one = new infopage(getcountyName());
           } catch (IOException ex) {
               throw new RuntimeException(ex);
           }
           frame.dispose();
       }
       if (e.getSource() == BACK) {
           frame.dispose();
           mainPage one = new mainPage();
       }


    }
}



    //need to find the correct county from the list
    //present any info in a succinct way
    //no cock like horse cock