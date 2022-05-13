import java.io.*;
import java.util.Scanner;

public class HotSpring {
    static Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static final int maxn = 200005;
    static Node[] nodes = new Node[maxn * 5];
    static long[] arr = new long[maxn];

    public static void main(String[] args) {
        for (int i = 0; i < nodes.length; i++) nodes[i] = new Node();
        int n = in.nextInt();
        for (int i = 1; i <= n; i++) arr[i] = in.nextLong();
        build(1, 1, n);
        int q = in.nextInt();
        long[] ans = new long[q];
        for (int i = 0; i < q; i++) {
            int l = in.nextInt();
            int r = in.nextInt();
            ans[i] = query(1, l, r).mmax;
        }
        for (long a : ans) out.println(a);
        out.close();
    }

    static void update(int p) {
        Node node = nodes[p];
        node.sum = nodes[p << 1].sum + nodes[p << 1 | 1].sum;
        node.lmax = max(nodes[p << 1].sum + nodes[p << 1 | 1].lmax, nodes[p << 1].lmax);
        node.rmax = max(nodes[p << 1 | 1].sum + nodes[p << 1].rmax, nodes[p << 1 | 1].rmax);
        node.mmax = max(max(nodes[p << 1].mmax, nodes[p << 1 | 1].mmax), nodes[p << 1].rmax + nodes[p << 1 | 1].lmax);
    }

    static void build(int p, int l, int r) {
        Node node = nodes[p];
        node.l = l;
        node.r = r;
        if (l == r) {
            node.sum = node.lmax = node.rmax = node.mmax = arr[r];
            return;
        }
        int m = (node.l + node.r) >> 1;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        update(p);
    }

    static Node query(int p, int l, int r) {
        Node node = nodes[p];
        if (l <= node.l && node.r <= r) return nodes[p];
        int m = (node.l + node.r) >> 1;
        if (r <= m)
            return query(p << 1, l, r);
        else if (l > m)
            return query(p << 1 | 1, l, r);
        else {
            Node x = query(p << 1, l, r), y = query(p << 1 | 1, l, r);
            Node ans = new Node();
            ans.sum = x.sum + y.sum;
            ans.lmax = max(x.sum + y.lmax, x.lmax);
            ans.rmax = max(y.sum + x.rmax, y.rmax);
            ans.mmax = max(max(x.mmax, y.mmax), x.rmax + y.lmax);
            return ans;
        }
    }

    static long max(long num1, long num2) {
        return Math.max(num1, num2);
    }

    static class Node {
        int l, r;
        long sum, lmax, rmax, mmax;
    }
}