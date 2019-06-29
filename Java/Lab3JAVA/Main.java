import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {



        Scanner scan = new Scanner(System.in);
        String a = scan.nextLine();
        a=a.replaceAll("\\s","");
        char[] str = a.toCharArray();
        if (str[0]!='A'&&str[0]!='A'){
            System.out.printf("Your sequence already cannot be correct as it starts with '%c'", str[0]);
            return;
        }
        if(a.equals("")) {
            System.out.println("Empty input.");
            return;
        }

        SequenceCheck stack = new SequenceCheck(str);

        stack.abcd();
        if(stack.was_error()){
            System.out.println("Not correct");
        }
        else
            System.out.println("Correct");

        return;
    }
}
