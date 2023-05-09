import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Survey extends mainPage implements ActionListener {

    JPanel background = new JPanel();
    int number = 0;
    String temp = new String();
    JFrame frame = new JFrame();
    JTextArea Question = new JTextArea(temp);
    JTextArea Response = new JTextArea();
    JButton Submit = new JButton("Enter");

    JButton BACK = new JButton("Back");

    Survey() {

        BufferedReader reader;

        try {
            reader = new BufferedReader(new FileReader("questions_input.txt"));
            temp = reader.readLine();

            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
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
        Question.setText(temp);
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

    public void actionPerformed(ActionEvent evt) {
        if (evt.getSource() == Submit) {


                String answer = Response.getText();
                System.out.println(answer);
                Response.setText("");


                BufferedReader reader;

                number++;
                Question.setPreferredSize(new Dimension(15, 250));
                if (number == 20) {
                    //end of Questions
                    frame.dispose();
                    calculations one = new calculations();


                } else {
                    try {
                        reader = new BufferedReader(new FileReader("questions_input.txt"));
                        for (int i = 0; i <= number; i++) {
                            temp = reader.readLine();
                        }
                        reader.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    Question.setText(temp);
                    SwingUtilities.updateComponentTreeUI(frame);

                }

        }
        if (evt.getSource() == BACK) {
            frame.dispose();
            mainPage one = new mainPage();
        }
        //other components here
    }
}
