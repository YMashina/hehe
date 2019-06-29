import java.util.ArrayList;
import java.util.Scanner;
import java.util.Arrays;

public class SequenceCheck extends MyStack {

    public static int waserror = 0;
    private void error(int er){
        waserror = 1;
        System.out.printf("\nSequence: %s",str);
        switch (er){
            case 1: System.out.printf("\nOdd symbols in input\n");
            case 2: System.out.printf("\nx1 and x2 don't match\n");
            case 3: System.out.printf("\nCan't pop from empty stack.\n");
            case 4: System.out.printf("\nStack is empty\n");
            case 5: System.out.printf("\nOdd characters at the end of the sequence\n");
            default: System.out.printf("\nNo other errors\n");
        }
    }

    boolean was_error(){
        if(waserror==1)
            return true;
        return false;
    }

    private void sequence_check(){
        if(counter!=chararray.length){
            error(5);
        }
    }

    int nooddsymbols(char a){
        if (a!='A'&&a!='B'&&a!='C'&&a!='D'&&a!='\n'){
            return 0;
        }
        return 1;
    }

    int abcd(){
        //char a;
        //while ((a=getchar())==' ')
        //    ;
        char a = chararray[j]; j++;

        System.out.printf("Processing: %c\n", a);
        if (nooddsymbols(a)==0){
            str.append(a); counter++;
            //str[(i)+1]='\0';
            (i)++;
            error(1);
            er = 0;
            return 0;
        }
        if (a=='C'){
            str.append(" C "); counter++;

            (i)+=3;
            if (check( 0)!=0)
                return 1;
            return 0;
        }
        str.append(a); counter++;
        //str[(*i)+1]='\0';
        (i)++;
        this.push( a);

        if(peek()==-1){
            error(4);
            return 0;
        }
        System.out.printf("on top of stack:%c\n", peek());
        if(abcd()==0)
            return 0;

        sequence_check();
        return 1;
    }

    int check( int dflag){
        //char a;
        //while ((a=getchar())==' ')
        //    ;
        char a = chararray[j]; j++;
        if (nooddsymbols(a)==0){
            str.append(a); counter++;
            //str[(*i)+1]='\0';
            (i)++;
            error(1);
            er = 0;
            return 0;
        }
        if(peek()==-1){
            error(4);
            return 0;
        }
        System.out.printf("on top of stack :%c\n", peek());
        System.out.printf("Processing: %c\n", a);
        if (a==peek()&& a !='D'){
            str.append(a); counter++;
            //str[(*i)+1]='\0';
            (i)++;
            if (!isEmpty())
                pop();

  		else {
                error(3);
        er = 0;
                return 0;
            }

        }
        else
        if (a !='D'){
            str.append(a); counter++;
            //str[(i)+1]='\0';
            (i)++;
            error(2);
        er = 0;
            return 0;
        }

        if (a=='D'){
            dflag = 1;
            str.append(" D "); counter++;

            //str[(*i)+3]='\0';
            (i)+=3;
            if ((isEmpty())&&(dflag!=0)){
                abcd();
            }
            else {
                error(2);
        er = 0;
                return 0;
            }
        }
        if (!isEmpty())
            if (check( dflag)!=0)
                return 1;

        //System.out.printf("Correct");
        return 5;

    }
    SequenceCheck(char [] array){
        chararray=Arrays.copyOf(array, array.length);
        str = new StringBuilder(array.length);
    }

    private static char[] chararray;
    private static int i = 0, j = 0, er;
    private static StringBuilder str;
    private static int counter = 0;

}
