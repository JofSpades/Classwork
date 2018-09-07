public class HugeInt{
    private String storedValue;

    //creates a blank instance of HugeInt
    public HugeInt(){
        this.storedValue = new String();
    }

    //used to initialize the object with a passed in string of the needed value
    public HugeInt(String inValue){
        this.storedValue = new String();
        while(!inValue.equals("0")){
            this.storedValue = oddsToOne(inValue) + this.storedValue;
            inValue = divideByTwo(inValue);
        }
    }

    //helper for finding the Binary string verions
    private String divideByTwo(String value){
        String newString = "";
        int add = 0;
        int newDigit;
        for(char ch: value.toCharArray()){
            newDigit = (((int)ch) - ((int)'0')) / 2 + add;
            newString += String.valueOf(newDigit);
            add = ((int)Integer.parseInt(oddsToOne(String.valueOf(ch)))) * 5;
        }
        if(!newString.equals("0") && newString.charAt(0) == '0'){
            newString = newString.substring(1);
        }
        return newString;

    }

    //helper used to get the current binary value string version
    private String oddsToOne(String s){
      int length = s.length();
      if(length == 0){
        if(s.charAt(0) == '1'){return "1";}
        if(s.charAt(0) == '3'){return "1";}
        if(s.charAt(0) == '5'){return "1";}
        if(s.charAt(0) == '7'){return "1";}
        if(s.charAt(0) == '9'){return "1";}
        return "0";
      } else {
        length -= 1;
        if(s.charAt(length) == '1'){return "1";}
        if(s.charAt(length) == '3'){return "1";}
        if(s.charAt(length) == '5'){return "1";}
        if(s.charAt(length) == '7'){return "1";}
        if(s.charAt(length) == '9'){return "1";}
        return "0";
      }
    }

    //get a copy of the stored value
    public String getValue(){
        return this.storedValue;
    }
    public void setValue(String in){
        this.storedValue = in;
    }

    //Helper for addition
    private String add(String a, String b, boolean sub){
        String c = new String();
        int length = Math.max(a.length(), b.length());
        while(a.length() < length){a = "0" + a;}
        while(b.length() < length){b = "0" + b;}
        int carry = 0;
        int first, second, sum;
        for(int i = length - 1; i >= 0; i--){
            first = (int)(a.charAt(i) - '0');
            second = (int)(b.charAt(i) - '0');
            sum = (first ^ second ^ carry) + '0';
            c = (char)sum + c;
            carry = (first & second) | (second & carry) | (first & carry);
        }
        if(carry == 1 && !sub){
            c = '1' + c;
        }
        return c;
    }

    //Addition wrapper
    public HugeInt add(HugeInt in){
        String a = this.getValue();
        String b = in.getValue();
        HugeInt retval = new HugeInt();
        retval.setValue(this.add(a,b, false));
        return retval;
    }

    //negate string
    private String negate(String a, int length){
        a = a.replaceAll("0", "x").replaceAll("1", "0").replaceAll("x", "1");
        while(a.length() < length){
            a = "1" + a;
        }
        a = this.add(a, "1", true);
        return a;
    }

    //subtraction
    public HugeInt sub(HugeInt in){
        String a = this.getValue();
        String b = in.getValue();
        HugeInt retval = new HugeInt();
        retval.setValue(this.sub(a,b));
        return retval;
    }

    //string subtraction
    public String sub(String a, String b){
        if(a.indexOf('1') == -1 && b.indexOf('1') == -1){
            return"0";
        }
        if(a.equals(b)){
            return "0";
        }
        String stepOne = this.negate(b,a.length());
        String stepTwo = this.add(a, stepOne, true);
        return stepTwo;
    }

    //multiplication wrapper
    public HugeInt mul(HugeInt in){
        String a = this.getValue();
        String b = in.getValue();
        HugeInt retval = new HugeInt();
        retval.setValue(this.mul(a, b));
        return retval;
    }

    //helper to multiply individual chars
    private String multiplySingleBits(String a, String b){
        if(a.equals("1") && b.equals("1")){return "1";}
        else {return "0";}
    }

    //multiplication of strings
    private String mul(String a, String b){
        int length = Math.max(a.length(), b.length());
        while(a.length() < length){a = "0" + a;}
        while(b.length() < length){b = "0" + b;}
        if(length == 0){return "0";}
        if(length == 1){return multiplySingleBits(a,b);}
        if(a.indexOf('1') == length-1){
            return b;
        } else if(b.indexOf('1') == length -1){
            return a;
        }
        int fHalf = (length / 2);
        int sHalf = (length - fHalf);
        String aLeft = a.substring(0, fHalf);
        String aRight = a.substring(fHalf);
        String bLeft = b.substring(0, fHalf);
        String bRight = b.substring(fHalf);
        String P1 = this.mul(aLeft, bLeft);
        String P2 = this.mul(aRight, bRight);
        String P3 = this.mul(this.add(aLeft,aRight,false), this.add(bLeft,bRight,false));
        String subtracted = this.sub(P3,P1);
        subtracted = this.sub(subtracted, P2);
        for(int i = 0; i < sHalf; i++){
            subtracted += "0";
            P1 += "00";
        }
        String c = this.add(P1,subtracted, false);
        c = this.add(c,P2,false);
        int index = c.indexOf('1');
        if(index != -1){
            c = c.substring(index);
        } else {
            c = "0";
        }
        return c;
    }

    //exponent this ^ in
    public HugeInt exp(HugeInt in){
        String a = this.getValue();
        String b = in.getValue();
        String c = a;
        HugeInt retval = new HugeInt();
        int index = b.indexOf('1');
        if(index != -1){
            if(index > 0){
                b = b.substring(index);
            }
        } else {
            retval.setValue(c);
            return retval;
        }
        int length = b.length();
        for(int i = 1; i < length; i++){
            c = this.mul(c,c);
            if(b.charAt(i) == '1'){
                c = this.mul(c,a);
            }
        }
        retval.setValue(c);
        return retval;
    }

    //division in/this
    public HugeInt div(HugeInt in){
        String a = this.getValue();
        String b = in.getValue();
        HugeInt retval = new HugeInt();
        retval.setValue(this.div(a, b));
        return retval;
    }

    //division of strings
    private String div(String n, String d){
        String q = "0";
        String r = "0";
        int nIndex = n.indexOf('1');
        int dIndex = d.indexOf('1');
        if(nIndex != -1 && dIndex != -1){
            if((n.length() - nIndex) < (d.length() - dIndex)){
                return "0";
            }
        } else if(nIndex != -1 && dIndex == -1){
            System.out.println("DIVIDE BY ZERO ERROR");
            System.exit(1);
        } else if(nIndex == -1 && dIndex != -1){
            return "0";
        }
        n = n.substring(nIndex);
        d = d.substring(dIndex);
        int length = Math.max(n.length(), d.length());
        while(q.length() < length){q += "0";}
        char[] middleQ = q.toCharArray();
        for(int i = 0; i < length; i++){
            if(n.charAt(i) == '1'){
                r += "1";
            } else {
                r += "0";
            }
            if(this.compare(r,d) >= 0){
                r = this.sub(r,d);
                middleQ[i] = '1';
            }
        }
        q = String.valueOf(middleQ);
        return q;
    }

    //compare a < b -1; a > b 1; a == b 0
    public int compare(HugeInt in){
        String a = this.getValue();
        String b = in.getValue();
        return this.compare(a, b);
    }
    private int compare(String a, String b){
        int length = Math.max(a.length(), b.length());
        while(a.length() < length){a = "0" + a;}
        while(b.length() < length){b = "0" + b;}
        if(a.compareTo(b) < 0){
            return -1;
        } else if(a.compareTo(b) > 0){
            return 1;
        } else {
            return 0;
        }
    }

    //modulus
    public HugeInt mod(HugeInt in){
        String a = this.getValue();
        String n = in.getValue();
        HugeInt retval = new HugeInt();
        if(this.compare(a,n) == -1){
            retval.setValue(a);
            return retval;
        }
        String temp = this.div(a,n);
        temp = this.mul(temp,n);
        temp = this.sub(a,temp);
        int index = temp.indexOf('1');
        if(index == -1){
            temp = "0";
        } else {
            temp = temp.substring(index);
        }
        while(this.compare(temp,n) >= 0){
            temp = this.sub(temp,n);
        }
        retval.setValue(temp);
        return retval;
    }
}
