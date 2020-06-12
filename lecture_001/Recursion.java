import java.util.ArrayList;

public class Recursion {
    public static void main(String[] args) {
        // System.out.println(subsequence_02("abc"));
        // System.out.println(nokiaKeyPad_01("459"));
        // System.out.println(nokiaKeyPad_02("459", ""));
        System.out.println(nokiaKeyPad_03("10110", ""));
    }

    public static int subsequence_01(String str, String ans) {
        if (str.length() == 0) {
            System.out.println(ans);
            return 1;
        }

        String nstr = str.substring(1);
        char ch = str.charAt(0);

        return subsequence_01(nstr, ans + ch) + subsequence_01(nstr, ans);
    }

    public static ArrayList<String> subsequence_02(String str) {
        if (str.length() == 0) {
            ArrayList<String> base = new ArrayList<>();
            base.add("");
            return base;
        }
        String nstr = str.substring(1);
        char ch = str.charAt(0);

        ArrayList<String> recAns = subsequence_02(nstr);

        int size = recAns.size();
        for (int i = 0; i < size; i++) {
            recAns.add(ch + recAns.get(i));
        }

        return recAns;
    }

    static String[] words = { "$&*", ":;", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", "+-/", "%^@" };

    public static ArrayList<String> nokiaKeyPad_01(String str) {
        if (str.length() == 0) {
            ArrayList<String> base = new ArrayList<>();
            base.add("");
            return base;
        }

        String nstr = str.substring(1);
        int idx = str.charAt(0) - '0';
        String word = words[idx];

        ArrayList<String> recAns = nokiaKeyPad_01(nstr);

        ArrayList<String> myAns = new ArrayList<>();
        for (int i = 0; i < word.length(); i++) {
            for (String string : recAns) {
                myAns.add(string + word.charAt(i));
            }
        }

        return myAns;
    }

    public static int nokiaKeyPad_02(String str, String ans) {
        if (str.length() == 0) {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        String nstr = str.substring(1);
        String word = words[str.charAt(0) - '0'];

        for (int i = 0; i < word.length(); i++) {
            count += nokiaKeyPad_02(nstr, ans + word.charAt(i));
        }

        return count;
    }

    public static int nokiaKeyPad_03(String str, String ans) {
        if (str.length() == 0) {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        String nstr = str.substring(1);
        int idx = str.charAt(0) - '0';
        String word = words[idx];

        for (int i = 0; i < word.length(); i++) {
            count += nokiaKeyPad_03(nstr, ans + word.charAt(i));
        }

        if (str.length() > 1 && idx==1) {
            nstr = str.substring(2);
            idx = idx * 10 + (str.charAt(1) - '0');
            if (idx >= 10 && idx <= 11) {
                word = words[idx];
                for (int i = 0; i < word.length(); i++) {
                    count += nokiaKeyPad_03(nstr, ans + word.charAt(i));
                }
            }
        }
        return count;
    }
}