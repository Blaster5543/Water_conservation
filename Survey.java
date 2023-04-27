import javax.swing.*;

public class Survey {

    String temp = new String("WHAT?");
    JFrame frame = new JFrame();
    JLabel Question = new JLabel(temp);
    JTextField Response = new JTextField();
    JButton Submit = new JButton("Enter");

    Survey() {

        Question.setBounds(200,150,80,200);
        frame.add(Question);

        Response.setBounds(100, 280, 200,20);
        frame.add(Response);

        Submit.setBounds(320,280,100,20);
        frame.add(Submit);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 600);
        frame.setLayout(null);
        frame.setVisible(true);



    }


}
