import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;;
import java.io.*;

public class Yesnt extends mainPage implements ActionListener {

    public  String temp = null;

    private JPanel background = new JPanel();
    private int number = 0;
    private JFrame frame = new JFrame();

    private JTextArea Question = new JTextArea();

    private  JButton YES = new JButton("Yes");

    private  JButton NO = new JButton("No");

    private JButton BACK = new JButton("Back");

    String Answers = "";

    public String getAnswers() {
        return Answers;
    }

    public void setAnswers(String answers) {
        Answers = answers;
    }

    Yesnt() {

        BufferedReader reader;

        try {
            reader = new BufferedReader(new FileReader("questions.txt"));
            temp = reader.readLine();

            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        BACK.setBounds (0,0,100,40);
        BACK.setFocusable(false);
        BACK.addActionListener(this);
        frame.add(BACK);

        Question.setBounds(150, 150, 200, 60);
        Font  f1  = new Font(Font.SANS_SERIF, Font.PLAIN,  16);
        Question.setFont(f1);
        Question.setLineWrap(true);
        Question.setWrapStyleWord(true);
        Question.setEditable(false);
        Question.setOpaque(false);
        Question.setBorder(new EmptyBorder(0,0,0,0));
        Question.setText(temp);
        frame.add(Question);

        YES.setBounds(150, 250, 100, 50);
        YES.addActionListener(this);
        frame.add(YES);

        NO.setBounds(250, 250, 100, 50);
        NO.addActionListener(this);
        frame.add(NO);

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

        frame.setSize(500, 600);
        frame.setLayout(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent evt) {
        BufferedReader reader;
        if (evt.getSource() == YES) {
            number++;
            Question.setPreferredSize(new Dimension(15,250));
            if (number == 15) {
                //end of Questions
                frame.dispose();
                Tips one = new Tips(Answers);

            } else {
                try {
                    reader = new BufferedReader(new FileReader("questions.txt"));
                    for (int i = 0; i <= number; i++) {
                        temp = reader.readLine();
                    }
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                Question.setText(temp);

                    //do something with the yes

                Answers = Answers + "Y";

                SwingUtilities.updateComponentTreeUI(frame);

            }
        }
        if (evt.getSource() == NO) {
            number++;

            if (number == 15) {
                //end of Questions
                frame.dispose();

                Tips one = new Tips(Answers);


            } else {
                try {
                    reader = new BufferedReader(new FileReader("questions.txt"));
                    for (int i = 0; i <= number; i++) {
                        temp = reader.readLine();
                    }
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                Question.setLineWrap(true);
                Question.setText(temp);


        //do something with the no.

                Answers = Answers + "N";
                //get to the next question
                SwingUtilities.updateComponentTreeUI(frame);

            }
        }
        if (evt.getSource() == BACK) {
            mainPage one = new mainPage();
        }
    }
}

