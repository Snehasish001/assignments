import java.lang.Math;

public class Tower {
    static SpecialStack t1;
    static SpecialStack t2;
    static SpecialStack t3;
    static int moves = 0;
    
    static void display() {
        int start = Math.max(t1.top, Math.max(t2.top, t3.top));
        for (int i = start; i >= 0; i--) {
            System.out.println("| "+t1.stk[i]+" |  | "+t2.stk[i]+" |  | "+t3.stk[i]+" |\n-----  -----  -----");
        }

        System.out.println("\t");
    }

    static void solve(int disk, SpecialStack s1, SpecialStack s2, SpecialStack s3) throws StackException {

        if (disk == 1) {
            int item = s1.pop();
            s3.push(item);

            display();
            moves++;
            return;
        }

        solve(disk - 1, s1, s3, s2);

        int item = s1.pop();
        s3.push(item);
        display();
        moves++;

        solve(disk - 1, s2, s1, s3);
    }

    public static void main(String[] args) {
        t1 = new SpecialStack(10);
        t2 = new SpecialStack(10);
        t3 = new SpecialStack(10);

        int disk = 5;
        for (int i = disk; i > 0; i--) {
            try{
                t1.push(i);
            } catch (Exception e) {
                continue;
            }
        }
        
        System.out.println("Initial : ");
        display();
        try {
            solve(disk, t1, t2, t3);
        } catch (Exception e) {
            System.out.println(e);
        }

        System.out.println("n = "+disk+"\nTotal moves = "+moves+"\nCalculated Moves = "+(int)(Math.pow(2, disk) - 1));
    }
}
