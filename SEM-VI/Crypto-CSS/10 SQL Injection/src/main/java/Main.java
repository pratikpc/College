import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

class Main {

    JPanel panel;
    JFrame jf;
    JLabel label1, label2;
    JButton login;
    JTextField usernameField;
    JPasswordField passwordfield;
    Connection c;

    public Main() throws  Exception{
        initComponents();
        handlingEvents();
        InitDB();
    }

    public boolean InsertUserName(Connection c, String username, String password) throws Exception{
            PreparedStatement ps = c.prepareStatement("INSERT OR REPLACE INTO auth(username, pass) values(?,?)");
            ps.setString(1, username);
            ps.setString(2, password);
            return ps.execute();

    }
    public void InitDB() throws Exception {
        Class.forName("org.sqlite.JDBC");
        c = DriverManager.getConnection("jdbc:sqlite::memory:");
        {
            Statement stmt = c.createStatement();
            stmt.executeUpdate("CREATE TABLE IF NOT EXISTS auth\n" +
                    "                (username text PRIMARY KEY NOT NULL, pass text NOT NULL)");
        }
        InsertUserName(c, "user", "pass");
    }

    public void initComponents() {
        jf = new javax.swing.JFrame();
        jf.setTitle("Login");
        jf.setLayout(null);
        jf.setSize(800, 500);
        jf.show();
        jf.setVisible(true);

        JScrollPane scrollBar = new JScrollPane(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        jf.add(scrollBar);

        label1 = new javax.swing.JLabel("User Login.To perform auth, anything' OR '1'='1");
        label1.setFont(new Font("Monotype Corsiva", Font.BOLD, 24));
        label1.setBounds(400, 20, 500, 40);
        jf.add(label1);

        label1 = new javax.swing.JLabel("Username");
        label1.setFont(new Font("Monotype Corsiva", Font.BOLD, 24));
        label1.setBounds(200, 80, 150, 40);
        jf.add(label1);

        usernameField = new javax.swing.JTextField();
        usernameField.setFont(new Font("Monotype Corsiva", Font.BOLD, 24));
        usernameField.setBounds(400, 80, 150, 30);
        usernameField.setToolTipText("Default Value: user");
        jf.add(usernameField);

        label1 = new javax.swing.JLabel("Password");
        label1.setFont(new Font("Monotype Corsiva", Font.BOLD, 24));
        label1.setBounds(200, 200, 100, 40);
        jf.add(label1);

        passwordfield = new javax.swing.JPasswordField();
        passwordfield.setFont(new Font("Monotype Corsiva", Font.BOLD, 24));
        passwordfield.setBounds(400, 200, 150, 30);
        passwordfield.setToolTipText("Default Value: pass");
        jf.add(passwordfield);

        login = new javax.swing.JButton("Login");
        login.setFont(new Font("Monotype Corsiva", Font.BOLD, 24));
        login.setBounds(250, 280, 100, 30);
        jf.add(login);

    }

    public void handlingEvents() {
        login.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                String user = usernameField.getText();
                String password = new String(passwordfield.getPassword());
                boolean valid = false;
                try {
                    System.out.println("3333 " + user + "  " + password);
                    Statement st = c.createStatement();
                    st.execute("SELECT COUNT(username) FROM auth WHERE username='" + user + "' AND pass='" + password + "'");
                    ResultSet rs = st.getResultSet();
                    valid = (rs.getInt(1) != 0);
                    st.close();
                } catch (Exception e) {
                }
                if (valid) {
                    JOptionPane.showMessageDialog(null, "Authenticated User");
                    usernameField.setText("");
                    passwordfield.setText("");
                } else {
                    JOptionPane.showMessageDialog(null, "Not Authenticated User");
                }

            }
        });

    }
    public static void main(String[] args) throws  Exception {
        Main log = new Main();
    }
}

