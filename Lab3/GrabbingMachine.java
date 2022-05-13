import java.io.*;
import java.util.Arrays;
import java.util.Scanner;

public class GrabbingMachine {
    static Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String[] args) {
        int n = in.nextInt();
        int m = in.nextInt();
        int max = in.nextInt();
        long time = in.nextLong();
        long[] bunny = new long[n];
        long[] nest = new long[m];
        int[] count = new int[m];
        int sum = 0;
        for (int i = 0; i < n; i++) bunny[i] = in.nextLong();
        for (int i = 0; i < m; i++) nest[i] = in.nextLong();
        // sort(bunny);
        // sort(nest);
        bunny = Arrays.stream(bunny).sorted().toArray();
        nest = Arrays.stream(nest).sorted().toArray();
        int i = 0;
        int j = 0;
        while (i != n && j != m) {
            if (bunny[i] < nest[j] && nest[j] - bunny[i] > time) {
                i++;
                continue;
            }
            if (nest[j] < bunny[i] && bunny[i] - nest[j] > time) {
                j++;
                continue;
            }
            if (Math.abs(nest[j] - bunny[i]) <= time) {
                count[j]++;
                sum++;
                i++;
            }
            if (count[j] == max) j++;
        }
        out.println(sum);
        out.close();
    }

    private static void sort(long[] array) {
        for (int gap = array.length / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < array.length; i++) {
                int j = i;
                long temp = array[j];
                while (j - gap >= 0 && temp < array[j - gap]) {
                    array[j] = array[j - gap];
                    j -= gap;
                }
                array[j] = temp;
            }
        }
    }
}
