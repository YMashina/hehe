import java.util.*;
import java.lang.*;
//import static sun.tools.java.Scanner.EOF;

public class PostfixOperations extends StackClass{
    //struct Stack stack = initStack();

    public int process() {
        char c = 1;
        int a, b;
        //for (c = getchar(); isspace(c) && c != '\n'; c = getchar()) ;
        //ungetc(c, stdin);
        //c = str[j]; j++;


        while ( j<size) {
            //for (; c==' ' && c != '\n'; c = getchar())

            c = str[j]; j++;
            if(c==' '){
                c = str[j]; j++;
            }

            if (Character.isLetter(c)) {
                System.out.printf("Error! Non-digital symbols found: %c.\n", c);
                //destroy(&stack);
                System.exit(1);
            }
            if (Character.isDigit(c)) {
                //ungetc(c, stdin);
                //scanf("%d", & n);
                StringBuilder temp = new StringBuilder(); int n = 0;
                while (c!=' '&&j!=size&& Character.isDigit(c)){
                    temp.append(c);
                    c = str[j]; j++;
                }
                n = Integer.parseInt(new String(temp.toString()));
                System.out.printf("pushed: ");
                push(n);
                continue;
            }
            if (c == '+') {
                a = pop();
                b = pop();
                System.out.printf("pushed: %d+%d = ", a, b);
                push(a + b);
                continue;
            }
            if (c == '-') {
                a = pop();
                b = pop();
                System.out.printf("pushed: %d-%d = ", b, a);
                push(b - a);
                continue;
            }
            if (c == '*') {
                a = pop();
                b = pop();
                System.out.printf("pushed: %d*%d = ", a, b);
                push(a * b);
                continue;
            }
            if (c == '^') {
                a = pop();
                b = pop();
                if (a < 0) {
                    System.out.printf("Sorry, don't want to calculate negative powers.\n");
                    //destroy(&stack);
                    System.exit(0);
                }
                System.out.printf("pushed: %d^%d = ", b, a);
                push((int)Math.pow(b, a));
                continue;
            }
            if(!(c=='\n'))
                System.out.printf("Error! Improper symbols found: %c.\n", c);
            //destroy(&stack);
            System.exit(1);
        }

        if (isEmpty()) {
            System.out.printf("Empty sequence!\n");
            return 0;
        }

        if (!isEmpty())
            System.out.printf("Error! Operation expected.\n");
       // else
            System.out.printf("Result of calculation: %d\n", pop());
        //destroy(&stack);
        return 0;
    }

    PostfixOperations(char [] array){
        size = array.length;
        str = Arrays.copyOf(array, size);
    }

    private static char[] str;
    private static int j = 0;
    private static int size = 0;
}
