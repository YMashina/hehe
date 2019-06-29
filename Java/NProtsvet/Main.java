import java.util.Scanner;
import java.io.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {

    public static void main(String[] args) throws Exception  {
        System.out.printf("Input the expression in postfix notation to calculate.\n");
        System.out.printf("Beware of the fact that postfix notation should not include any brackets or variables.\n\n");
        //Scanner scan = new Scanner(System.in);
        //String a = scan.nextLine();
        String a;
        StringBuilder sb = new StringBuilder();

        try (BufferedReader br = Files.newBufferedReader(Paths.get(System.getProperty("user.dir")+"/postfix.txt"))) {

            // read line by line
            String line;
            while ((line = br.readLine()) != null) {
                sb.append(line).append("\n");
            }

        } catch (IOException e) {
            System.err.format("IOException: %s%n", e);
        }

        //System.out.println(sb);


        a=sb.toString();

        System.out.println(a);
        a=a.replaceAll(" +"," ");
        //System.out.println(a);

        char[] str = a.toCharArray();

        if(a.equals("")) {
            System.out.println("Empty input.");
            return;
        }

        PostfixOperations op = new PostfixOperations(str);

        op.process();


        return;
    }
}
