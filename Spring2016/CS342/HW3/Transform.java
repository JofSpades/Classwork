import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.charset.Charset;
import java.io.IOException;
import java.util.List;
import java.io.*;
import java.util.*;
import java.io.File;
import javax.swing.*;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
public class Transform{

    private HugeInt n;
    private HugeInt d;
    private HugeInt e;

    public Transform(){}

    //loads the value for e and n from publicKey.xml file then starts the encrypting
    public void encryptToFile(String blockFile, String keyFile, String destFile) throws IOException
    {
        try {
            File fXmlFile = new File(keyFile);
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(fXmlFile);
            doc.getDocumentElement().normalize();
            NodeList nList = doc.getElementsByTagName("rsakey");
            Node nNode = nList.item(0);
            if(nNode.getNodeType() == Node.ELEMENT_NODE){
                Element eElement = (Element) nNode;
                this.e = new HugeInt(eElement.getElementsByTagName("evalue").item(0).getTextContent());
                this.n = new HugeInt(eElement.getElementsByTagName("nvalue").item(0).getTextContent());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        Path block_path = Paths.get(blockFile);
        byte[] blocks;
        try{
            blocks = Files.readAllBytes(block_path);
            try{
                String decodedBlocks = new String(blocks, "UTF-8");
                String[] splitBlocks= decodedBlocks.split("\n");
                List<String> outBlocks = new ArrayList<>();
                for(String value: splitBlocks){
                    outBlocks.add(this.convertb10(this.encrypt(new HugeInt(value)).getValue()));
                    System.out.println("LINE FINISHED");
                }
                Path encryptPath = Paths.get(destFile);
                Files.write(encryptPath, outBlocks, Charset.forName("UTF-8"));
                System.out.println("FILE ENCRYPTED");
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            }
        } catch (IOException e){
            JOptionPane.showMessageDialog(null, "File input error.", "Error",
                        JOptionPane.ERROR_MESSAGE);
            System.err.format("IOException: %s%n", e);
        }
    }

    //loads the values for d and n from the privateKey.xml file then stars decryption
    public void decryptToFile(String blockFile, String keyFile, String destFile) throws IOException
    {
        try {
            File fXmlFile = new File(keyFile);
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(fXmlFile);
            doc.getDocumentElement().normalize();
            NodeList nList = doc.getElementsByTagName("rsakey");
            Node nNode = nList.item(0);
            if(nNode.getNodeType() == Node.ELEMENT_NODE){
                Element eElement = (Element) nNode;
                this.d = new HugeInt(eElement.getElementsByTagName("dvalue").item(0).getTextContent());
                this.n = new HugeInt(eElement.getElementsByTagName("nvalue").item(0).getTextContent());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        Path block_path = Paths.get(blockFile);
        byte[] blocks;
        try{
            blocks = Files.readAllBytes(block_path);
            try{
                String decodedBlocks = new String(blocks, "UTF-8");
                String[] splitBlocks= decodedBlocks.split("\n");
                List<String> outBlocks = new ArrayList<>();
                int i = 1;
                int length = 0;
                String tmp;
                for(String value: splitBlocks){
                    tmp = this.convertb10(this.decrypt(new HugeInt(value)).getValue());
                    System.out.println("LINE FINISHED");
                    if(tmp.length() % 2 == 1){ tmp = "0"+tmp;}
                    if(tmp.length() > length){length = tmp.length();}
                    else{while(tmp.length() < length){tmp = "0" + tmp;}}
                    outBlocks.add(tmp);
                }
                Path encryptPath = Paths.get(destFile);
                Files.write(encryptPath, outBlocks, Charset.forName("UTF-8"));
                System.out.println("FILE DECRYPTED");
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            }
        } catch (IOException e){
            JOptionPane.showMessageDialog(null, "File input error.", "Error",
                        JOptionPane.ERROR_MESSAGE);
            System.err.format("IOException: %s%n", e);
        }
    }

    //encryption by fast modular exponenation wrapper
    public HugeInt encrypt(HugeInt in){
        HugeInt retval = new HugeInt("1");
        String eVal = this.e.getValue();
        String power = "1";
        HugeInt powerInt = new HugeInt();
        int percentage;
        for(int i = eVal.length() - 1; i >= 0; i--){
            if(eVal.charAt(i) == '1'){
                powerInt.setValue(power);
                retval = retval.mul(fstExponentMod(in, powerInt, this.n));
            }
            System.out.print("\r[");
            percentage = (int)(((eVal.length() - i) * 20)/eVal.length());
            for(int j = 0; j < percentage; j++){
                System.out.print("#");
            }
            for(int j = percentage; j < 20; j++){
                System.out.print(" ");
            }
            System.out.print("]");
            power += "0";
        }
        retval = retval.mod(this.n);
        System.out.println("");
        return retval;
    }
    //decryption by fast modular exponentiation wrapper
    public HugeInt decrypt(HugeInt in){
        HugeInt retval = new HugeInt("1");
        String dVal = this.d.getValue();
        String power = "1";
        HugeInt powerInt = new HugeInt();
        int percentage;
        for(int i = dVal.length() - 1; i >= 0; i--){
            if(dVal.charAt(i) == '1'){
                powerInt.setValue(power);
                retval = retval.mul(fstExponentMod(in, powerInt, this.n));
            }
            System.out.print("\r[");
            percentage = (int)(((dVal.length() - i) * 20)/dVal.length());
            for(int j = 0; j < percentage; j++){
                System.out.print("#");
            }
            for(int j = percentage; j < 20; j++){
                System.out.print(" ");
            }
            System.out.print("]");
            power += "0";
        }
        retval = retval.mod(this.n);
        System.out.println("");
        return retval;
    }

    //quickly finds the value returned from c^e mod n
    private HugeInt fstExponentMod(HugeInt c, HugeInt e, HugeInt n){
        if(e.compare(new HugeInt("1")) <= 0){
            return c.mod(n);
        }
        String tmp = e.getValue();
        e.setValue(tmp.substring(0,(tmp.length() - 1)));
        HugeInt returns = fstExponentMod(c, e, n);
        returns = returns.mul(returns);
        returns = returns.mod(n);
        return returns;
    }

    //converts binary string to base 10 string
    private String convertb10(String in){
        String retval = "0";
        String two = "1";
        for(int i = in.length()-1; i >= 0; i--){
            if(in.charAt(i) == '1'){
                retval = this.base10Add(retval, two);
            }
            two = this.base10Add(two,two);
        }
        return retval;
    }

    //addition of two base 10 strings
    private String base10Add(String a, String b){
        String retval = "";
        int aVal, bVal, length, carry;
        carry = 0;

        length = Math.max(a.length(), b.length());
        while(a.length() < length){a = "0" + a;}
        while(b.length() < length){b = "0" + b;}

        for(int i = length - 1; i >= 0; i--){
            aVal = (int)(a.charAt(i) - '0');
            bVal = (int)(b.charAt(i) - '0');
            carry = aVal + bVal + carry;
            if(carry >= 10){
                carry -= 10;
                retval = String.valueOf(carry) + retval;
                carry = 1;
            } else {
                retval = String.valueOf(carry) + retval;
                carry = 0;
            }
        }
        if(carry == 1){
            retval = "1" + retval;
        }
        return retval;
    }
}
