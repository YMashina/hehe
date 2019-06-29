import static java.lang.System.exit;
class StackClass {
    private class Node {
        int data;
        Node node;
    }

    StackClass(){
        this.top = null;
    }

    public int pop()
    {
        if (top == null) { // to avoid stack Underflow
            System.out.print("\nStack Underflow\n");
            return -1;
        }
        System.out.printf("%d popped from stack\n", top.data);
        // update the top pointer to point to the next node
        int tmp = top.data;
        top = (top).node;
        return tmp;
    }

    public void push(int x)
    {
        System.out.printf("%d pushed to stack\n", x);
        Node temp = new Node();

        if (temp == null) {//to avoid stack overflow
            System.out.print("\nStack Overflow\n");
            return;
        }

        temp.data = x;
        temp.node = top;
        top = temp;
    }

    public boolean isEmpty()
    {
        return top == null;
    }

    public int peek()
    {
        if (!isEmpty())
            return top.data;
        else
            return -1;
    }

    protected Node top;
} 