import java.io.*;
import java.util.*;

public class Moderate {
    static Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)), true);
    static final int maxn = 50005;
    static int cnt = 0, tar;
    static int[] arr;
    static int[] cpy;
    static int[] tree = new int[maxn];
    static int[] sum = new int[maxn << 5];
    static int[] left = new int[maxn << 5];
    static int[] right = new int[maxn << 5];
    static HashMap<Integer, Node> map = new HashMap<>();
    static List<Integer> list = new ArrayList<>();

    public static void main(String[] args) {
        int n = in.nextInt();
        int q = in.nextInt();
        arr = new int[n + 1];
        cpy = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            int x = in.nextInt();
            map.put(x, new Node(x));
            arr[i] = x;
            cpy[i] = x;
        }
        Arrays.sort(cpy);
        int temp = 0;
        for (int i = 1; i <= n; i++) {
            if (i == 1) {
                temp = cpy[i];
                list.add(temp);
                map.get(cpy[i]).pos = i;
                continue;
            }
            if (cpy[i] != temp) {
                list.add(cpy[i]);
                temp = cpy[i];
                map.get(cpy[i]).pos = i;
            }
        }
        int m = list.size();
        for (int i = 1; i <= n; i++) {
            tar = map.get(arr[i]).pos;
            tree[i] = update(tree[i - 1], 1, m);
        }
        int[] ans = new int[q];
        for (int i = 0; i < q; i++) {
            int l = in.nextInt();
            int r = in.nextInt();
            if (((r - l) & 1) == 0) tar = ((r - l) >> 1) + 1;
            else tar = (r - l + 1) >> 1;
            int pos = query(tree[l - 1], tree[r], 1, m, tar);
            ans[i] = cpy[pos];
        }
        for (int a : ans) out.println(a);
    }

    private static class Node {
        int val, pos;

        Node(int val) {
            this.val = val;
        }
    }

    static int update(int pre, int l, int r) {
        int pos = ++cnt;
        left[pos] = left[pre];
        right[pos] = right[pre];
        sum[pos] = sum[pre] + 1;
        if (l < r) {
            int m = (l + r) >> 1;
            if (tar <= m) left[pos] = update(left[pre], l, m);
            else right[pos] = update(right[pre], m + 1, r);
        }
        return pos;
    }

    static int query(int li, int ri, int l, int r, int m) {
        if (l >= r) return l;
        int p = sum[left[ri]] - sum[left[li]];
        int mid = (r + l) >> 1;
        if (p >= m) return query(left[li], left[ri], l, mid, m);
        else return query(right[li], right[ri], mid + 1, r, m - p);
    }
}
