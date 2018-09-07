import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.charset.Charset;
import java.io.IOException;
import java.io.*;
import java.io.File;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class RSAKeyGen{
    private HugeInt p;
    private HugeInt q;
    private HugeInt n;
    private HugeInt phi;
    private HugeInt e;
    private HugeInt d;
    private String primesFileName;

    //constructor for primes in file
    public RSAKeyGen(){
        this.primesFileName = "primes.rsc";
    }

    //fast exponent mod
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

    //sets the p and q values from the file name
    public void getPrimes(){
        Path primes_path = Paths.get(this.primesFileName);
        String[] primes = new String[20];
        Charset charset = Charset.forName("US-ASCII");
        int i = 0;
        try(BufferedReader reader = Files.newBufferedReader(primes_path, charset)){
            String line;
            while((line = reader.readLine()) != null){
                primes[i++] = line;
            }
        } catch (IOException e){
            System.err.format("IOException: %s%n", e);
        }
        int firstPrime = (int)(Math.random()*20);
        int secondPrime = (int)(Math.random()*20);
        while(firstPrime == secondPrime){
            firstPrime = (int)(Math.random()*20);
            secondPrime = (int)(Math.random()*20);
        }
        this.p = new HugeInt(primes[firstPrime]);
        System.out.println("P has been set: "+this.p.getValue());
        this.q = new HugeInt(primes[secondPrime]);
        System.out.println("Q has been set: "+this.q.getValue());
    }

    //based on the randomly selected p and q fro mthe file will generate n phi and d
    public void generateKeys(){
        HugeInt one = new HugeInt("1");
        HugeInt two = new HugeInt("2");
        this.n = p.mul(q);
        System.out.println("N has been set: "+this.n.getValue());
        HugeInt p1 = p.sub(one);
        HugeInt q1 = q.sub(one);
        this.phi = p1.mul(q1);
        System.out.println("Phi has been set: "+this.phi.getValue());
        this.e = new HugeInt("32769");
        int count = (int)(Math.random()*1000);
        while(count < 100){
            count = (int)(Math.random()*1000);
        }
        while(this.e.compare(this.n) < 0){
            if(this.gcd(this.e, this.phi).compare(one) == 0){
                count --;
                if(count == 0){
                    break;
                }
            }
            this.e = this.e.add(two);
        }
        if(this.e.compare(this.n) == 0){
            System.out.println("E NOT FOUND\nEXITING");
            System.exit(1);
        }
        System.out.println("E has been set: "+this.e.getValue());
        this.d = this.modinv(this.phi, this.e);
        this.d.setValue(this.d.getValue().substring(this.d.getValue().indexOf('1')));
        System.out.println("D has been set: "+this.d.getValue());

        // all values have been found and will now be saved to file
        try{
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc = docBuilder.newDocument();

            Element rootElement = doc.createElement("rsakey");
            doc.appendChild(rootElement);

            Element evalue = doc.createElement("evalue");
            evalue.appendChild(doc.createTextNode(this.convertb10(this.e.getValue())));
            rootElement.appendChild(evalue);

            Element nvalue = doc.createElement("nvalue");
            nvalue.appendChild(doc.createTextNode(this.convertb10(this.n.getValue())));
            rootElement.appendChild(nvalue);

            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);

            StreamResult result = new StreamResult(new File("publicKey.xml"));
            transformer.transform(source, result);

            docFactory = DocumentBuilderFactory.newInstance();
            docBuilder = docFactory.newDocumentBuilder();
            doc = docBuilder.newDocument();
            rootElement = doc.createElement("rsakey");
            doc.appendChild(rootElement);

            Element dvalue = doc.createElement("dvalue");
            dvalue.appendChild(doc.createTextNode(this.convertb10(this.d.getValue())));
            rootElement.appendChild(dvalue);

            Element prnvalue = doc.createElement("nvalue");
            prnvalue.appendChild(doc.createTextNode(this.convertb10(this.n.getValue())));
            rootElement.appendChild(prnvalue);

            transformerFactory = TransformerFactory.newInstance();
            transformer = transformerFactory.newTransformer();
            source = new DOMSource(doc);
            result = new StreamResult(new File("privateKey.xml"));
            transformer.transform(source, result);
        } catch (ParserConfigurationException pce) {
            pce.printStackTrace();
        } catch (TransformerException tfe) {
            tfe.printStackTrace();
        }
    }

    //used to find d by modular inverse
    private HugeInt modinv(HugeInt a, HugeInt b){
        HugeInt retval = new HugeInt();
        HugeInt one = new HugeInt("1");
        HugeInt zero = new HugeInt("0");
        HugeInt k = zero;
        HugeInt top = k;
        HugeInt temp = k;
        do{
            k = k.add(one);
            top = k.mul(a);
            top = top.add(one);
            temp = top.mod(b);
        }while(temp.compare(zero) != 0);
        System.out.println("Found mod 0");
        retval = top.div(b);
        return retval;
    }

    //Euclidean GCD implementation
    private HugeInt gcd(HugeInt a, HugeInt b){
        HugeInt zero = new HugeInt("0");
        if(a.compare(zero) == 0){
            return b;
        }
        if(b.compare(zero) == 0){
            return a;
        }
        HugeInt c = a.mod(b);
        return gcd(b,c);
    }

    //converts the binary string into base 10
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

    //addition of base 10 strings
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
