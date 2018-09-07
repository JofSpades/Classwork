import java.io.*;

public class Blocking {

    //takes input file and turns the text into coded values blocks then write to output file
    public static void block(String inFile, int bSize, String outFile) throws IOException {
        FileReader input = null;
        FileWriter output = null;
        char[] cbuf = new char[bSize];
        String[] sbuf = new String[bSize];

        try {
            input = new FileReader(inFile);
            output = new FileWriter(outFile);
            File f = new File(inFile);
            long fLen = f.length();

            int i = 0;
            while (input.read(cbuf, 0, bSize) != -1) {
                rev(cbuf);
                convert(cbuf, sbuf, true);

                if (i > (fLen - bSize))      //pad last line
                    pad(sbuf, bSize, fLen);

                i += bSize;

                for (int j = 0; j < bSize; j++)    //write to file
                    output.write(sbuf[j], 0, 2);
                output.write('\n');
            }
        } finally {
            if (input != null)
                input.close();
            if (output != null)
                output.close();
        }
    }

    //takes input blocked file and produces the original message in new file
    public static void unblock(String inFile, String outFile) throws IOException {
        FileReader input = null;
        FileWriter output = null;
        BufferedReader br;
        String[] sbuf;
        char[] cbuf;

        try {
            input = new FileReader(inFile);
            br = new BufferedReader(input);
            output = new FileWriter(outFile);

            String line;
            while ((line = br.readLine()) != null) {
                int len = line.length() / 2;
                sbuf = new String[len];
                cbuf = new char[len];
                sbuf = line.split("(?<=\\G..)", len);

                rev(sbuf);
                convert(cbuf, sbuf, false);
                output.write(cbuf);
            }
        } finally {
            if (input != null)
                input.close();
            if (output != null)
                output.close();
        }
    }

    private static void rev(char[] a) {
        int l = a.length;
        for (int i = 0; i < l / 2; i++) {
            char temp = a[i];
            a[i] = a[l - i - 1];
            a[l - i - 1] = temp;
        }
    }

    private static void rev(String[] b) {
        int l = b.length;
        for (int i = 0; i < l / 2; i++) {
            String temp = b[i];
            b[i] = b[l - i - 1];
            b[l - i - 1] = temp;
        }
    }

    //padding for the last line as needed
    private static void pad(String[] b, int size, long len) {
        long mod = len % size;
        if (mod != 0)
            for (int i = 0; i < (size - mod); i++)
                b[i] = "00";
    }

    //flag determines which way to convert
    //true converts ascii values to values in new alphabet
    //false converts coded values back to ascii
    private static void convert(char[] a, String[] b, boolean flag) {
        int l = a.length;
        for (int i = 0; i < l; i++) {
            if (flag) {
                if (a[i] == '\0')
                    b[i] = "00";
                else if (a[i] == (char) 11)
                    b[i] = "01";
                else if (a[i] == '\t')
                    b[i] = "02";
                else if (a[i] == '\n')
                    b[i] = "03";
                else if (a[i] == '\r')
                    b[i] = "04";
                else if (a[i] < '%')
                    b[i] = "0" + (Integer.toString(a[i] - 27));
                else
                    b[i] = Integer.toString(a[i] - 27);
            }
            else {
                a[i] = (char) Integer.parseInt(b[i]);

                if (a[i] == 0)
                    a[i] = '\0';
                else if (a[i] == 1)
                    a[i] = (char) 11;
                else if (a[i] == 2)
                    a[i] = '\t';
                else if (a[i] == 3)
                    a[i] = '\n';
                else if (a[i] == 4)
                    a[i] = '\r';
                else
                    a[i] += 27;
            }
        }
    }
}
