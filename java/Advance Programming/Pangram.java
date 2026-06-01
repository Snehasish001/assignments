public class Pangram {

    boolean isPangram(String input) {
        if (input.length() < 26) {
            return false;
        }
        
        String testSet = "abcdefghijklmnopqrstuvwxyz";
        boolean ans = false;
        for (int j = 0; j < testSet.length(); j++) {
            boolean inter = false;
            for (int i = 0; i < input.length(); i++) {
                if(testSet.charAt(j) == testSet.charAt(i)) {
                    inter = true;
                    break;
                }
            }
            if (inter == true) {
                ans = true;
            } else {
                ans = false;
                break;
            }
        }
        return ans;
    }
    public static void main(String[] args) {
        String str = "qwertyuiopasdfggm";

        Pangram p = new Pangram();
        if (p.isPangram(str)) {
            System.out.println(str+" : is Pangram");
        } else {
            System.out.println(str+" : is not Pangram");
        }
    }
}
