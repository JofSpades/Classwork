import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.io.File;
public class RSAGUI extends JFrame {

    public static void main(String[] args) {
        RSAGUI app = new RSAGUI();
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private JButton KeyGen, Block, Unblock, Crypt;
    private JTextField fName1, fName2, fName3, size;

    public RSAGUI() {
        super("RSA Encryption Program");
        setLayout(new GridLayout(4, 1, 0, 0));

        MouseHandler handler = new MouseHandler();

        KeyGen = new JButton("Key Creation");
        KeyGen.addMouseListener(handler);
        add(KeyGen);

        Block = new JButton("Block a file");
        Block.addMouseListener(handler);
        add(Block);

        Unblock = new JButton("Unblock a file");
        Unblock.addMouseListener(handler);
        add(Unblock);

        Crypt = new JButton("Encrypt / Decrypt");
        Crypt.addMouseListener(handler);
        add(Crypt);

        fName1 = new JTextField();
        fName2 = new JTextField();
        fName3 = new JTextField();
        size = new JTextField();

        setLocationRelativeTo(null);
        setSize(300, 250);
        setVisible(true);
    }

    private class MouseHandler implements MouseListener {
        public void mouseClicked (MouseEvent e)
        {
            if(e.getSource() == KeyGen){
                RSAKeyGen keygen = new RSAKeyGen();

                keygen.getPrimes();
                JOptionPane.showMessageDialog(null, "Primes generated from 'primes.rsc'",
                            "Random Primes", JOptionPane.INFORMATION_MESSAGE);
                keygen.generateKeys();
                JOptionPane.showMessageDialog(null, "Private and public keys generated and stored in files.");
            }
            else if(e.getSource() == Block) {
                doBlock();
            }
            else if(e.getSource() == Unblock){
                doUnblock();
            }
            else if(e.getSource() == Crypt){
                doTransform();
            }
        }

        public void mousePressed(MouseEvent e) {}

        public void mouseReleased(MouseEvent e) {}

        public void mouseEntered(MouseEvent e) {}

        public void mouseExited(MouseEvent e) {}
    }

    //doX helpers to perform operations when the respective button is clicked
    private void doBlock() {
        try {
            Object[] input = {"Message Filename: ", fName1, "Blocking Size: ", size,
                                "New Filename: ", fName2};
            int option = JOptionPane.showConfirmDialog(null, input, "Block File", JOptionPane.OK_CANCEL_OPTION);
            if (option == JOptionPane.OK_OPTION) {
                if(Integer.parseInt(size.getText()) > 8) {
                    int opt2 = JOptionPane.showConfirmDialog(null, "En/Decryption for block sizes greater than 8" +
                                    " not supported.\nRun time may be very long.\nPress 'Cancel' to go back.",
                                    "Block Size Warning!", JOptionPane.OK_CANCEL_OPTION);
                    if(opt2 == JOptionPane.CANCEL_OPTION)
                        return;
                }

                Blocking.block(fName1.getText(), Integer.parseInt(size.getText()), fName2.getText());
                JOptionPane.showMessageDialog(null, "Blocked file generated", "Block File",
                            JOptionPane.INFORMATION_MESSAGE);
            }
        }
        catch (IOException e){
            JOptionPane.showMessageDialog(null, "File input error.", "Error",
                        JOptionPane.ERROR_MESSAGE);
        }
    }

    private void doUnblock() {
        try{
            Object[] input = {"Blocked Filename: ", fName1, "Unblocked Filename: ", fName2};
            int option = JOptionPane.showConfirmDialog(null, input, "Unblock File", JOptionPane.OK_CANCEL_OPTION);
            if (option == JOptionPane.OK_OPTION) {
                Blocking.unblock(fName1.getText(), fName2.getText());
                JOptionPane.showMessageDialog(null, "File unblocked", "Unblock File",
                            JOptionPane.INFORMATION_MESSAGE);
            }
        }
        catch (IOException e){
            JOptionPane.showMessageDialog(null, "File input error.", "Error",
                        JOptionPane.ERROR_MESSAGE);
        }
    }

    private void doTransform(){
        Object[] input = {"Blocked Filename: ", fName1, "Key Filename: ", fName3,
                "Destination Filename: ", fName2};
        int option = JOptionPane.showConfirmDialog(null, input, "Encrypt/Decrypt", JOptionPane.OK_CANCEL_OPTION);
        if (option == JOptionPane.OK_OPTION) {
            String bf = fName1.getText();
            String kf = fName3.getText();
            String df = fName2.getText();
            Transform transformation = new Transform();
            try {
                File fXmlFile = new File(kf);
                if(!fXmlFile.exists()) {
                    JOptionPane.showMessageDialog(null, "File input error.", "Error",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }
                DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
                Document doc = dBuilder.parse(fXmlFile);
                doc.getDocumentElement().normalize();
                NodeList nList = doc.getElementsByTagName("rsakey");
                Node nNode = nList.item(0);
                if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element eElement = (Element) nNode;
                    NodeList nodeList = eElement.getElementsByTagName("evalue");
                    if (nodeList.getLength() == 0) {
                        transformation.decryptToFile(bf, kf, df);
                    } else {
                        transformation.encryptToFile(bf, kf, df);
                    }
                }
                JOptionPane.showMessageDialog(null, "File processed.", "Encrypt/Decrypt",
                        JOptionPane.INFORMATION_MESSAGE);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

}
